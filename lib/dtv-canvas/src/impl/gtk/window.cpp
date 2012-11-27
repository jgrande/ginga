#include "window.h"
#include "system.h"
#include "videooverlay.h"
#include "../cairo/canvas.h"
#include "../cairo/surface.h"
#include <util/log.h>
#include <util/mcr.h>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <gtk/gtk.h>

namespace canvas {
namespace gtk {

namespace impl {
	System *getSystem();
}

util::key::type getKeyCode( guint symbol );

#if GTK_MAJOR_VERSION >= 3
static gboolean on_window_draw( GtkWidget *da, cairo_t * /*cr*/, gpointer user_data ) {
	Rect rect( 0, 0, 720, 576 );//	TODO: Parametrize in GTK3?!
	Window *vo = (Window *)user_data;
	assert(vo);
	vo->draw( da, rect );
	return TRUE;
}
#else
static gboolean on_window_expose_event( GtkWidget *da, GdkEventExpose *event, gpointer user_data ) {
	Rect rect( event->area.x, event->area.y, event->area.width, event->area.height );
	Window *vo = (Window *)user_data;
	assert(vo);
	vo->draw( da, rect );
	return TRUE;
}
#endif

static gboolean key_press_cb( GtkWidget * /*widget*/, GdkEventKey *kevent, gpointer /*user_data*/ ) {
	impl::getSystem()->onKeyEvent( getKeyCode(kevent->keyval), kevent->type == GDK_KEY_RELEASE );
	return TRUE;
}

static void on_window_destroyed( GtkWidget * /*widget*/, gpointer /*user_data*/ ) {
	impl::getSystem()->onWindowDestroyed();
}

static gboolean on_event( GtkWindow * /*window*/, GdkEvent *event, gpointer user_data ) {
	Window *vo = (Window *)user_data;
	assert(vo);
	vo->updateWindow( event );
	return FALSE;
}

Window::Window()
{
	_surface = NULL;
	_window = NULL;
}

Window::~Window()
{
}

//	Initialization
bool Window::initialize() {
	LDEBUG("gtk::Window", "Initialize");

	//	Create main window
	gdk_threads_enter ();
	_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	assert(_window);
	g_object_ref( _window );

	//	Setup main window
	gtk_widget_set_events( GTK_WIDGET(_window),  GDK_STRUCTURE_MASK | GDK_FOCUS_CHANGE );	
	//gtk_widget_set_events( GTK_WIDGET(_window), GDK_ALL_EVENTS_MASK );
	gtk_window_set_title( GTK_WINDOW(_window), title().c_str() );
	gtk_window_set_position(GTK_WINDOW(_window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(_window), FALSE);
	gtk_widget_set_app_paintable(_window, TRUE);
	gtk_widget_set_double_buffered(_window, FALSE);

	//	Setup mode [FULLSCREEN | NORMAL]
	setMode();

	{	//	Set window to work with RGBA
		GdkScreen *screen = gtk_widget_get_screen(_window);
		gtk_widget_set_colormap( _window, gdk_screen_get_rgba_colormap(screen) );
	}

	{	//	Setup background color to black
		GdkColor color;
		gdk_color_parse ("black", &color);
		gtk_widget_modify_bg (_window, GTK_STATE_NORMAL, &color);
	}

	//	Setup window signals
#if GTK_MAJOR_VERSION >= 3
	g_signal_connect( G_OBJECT(_window), "draw", G_CALLBACK(on_window_draw), this);
#else
	g_signal_connect( G_OBJECT(_window), "expose_event", G_CALLBACK(on_window_expose_event), this);
#endif
	g_signal_connect( GTK_OBJECT(_window), "key_press_event", GTK_SIGNAL_FUNC(key_press_cb), this );
	g_signal_connect( GTK_OBJECT(_window), "key_release_event", GTK_SIGNAL_FUNC(key_press_cb), this );
	g_signal_connect( GTK_OBJECT(_window), "destroy", G_CALLBACK (on_window_destroyed), this);
	g_signal_connect( GTK_WIDGET(_window), "configure-event", G_CALLBACK(on_event), this );
	g_signal_connect( GTK_WIDGET(_window), "unmap-event", G_CALLBACK(on_event), this );
	g_signal_connect( GTK_WIDGET(_window), "map-event", G_CALLBACK(on_event), this );	
	g_signal_connect( GTK_WIDGET(_window), "focus-in-event", G_CALLBACK(on_event), this );

	//	Show window
	gtk_widget_show_all(_window);

	gdk_threads_leave ();

	return true;
}

void Window::setFullscreenMode() {
	assert(_window);
	gtk_window_fullscreen(GTK_WINDOW(_window));

	//	Set the new windows size (fullscreen size)
	GdkScreen *scr = gtk_window_get_screen(GTK_WINDOW(_window));
	int w = gdk_screen_get_width(scr);
	int h = gdk_screen_get_height(scr);
	setSize(w, h);
}

void Window::setNormalMode() {
	assert(_window);

	const Size &s = size();

	GdkGeometry hints;
	hints.min_width = s.w;
	hints.min_height = s.h;
	hints.width_inc = s.w;
	hints.height_inc = s.h;

	GdkWindowHints mask = (GdkWindowHints) (GDK_HINT_RESIZE_INC | GDK_HINT_MIN_SIZE );

	gtk_window_set_geometry_hints (GTK_WINDOW (_window),
			_window,
			&hints,
			mask);
}

void Window::finalize() {
	//	Remove window
	gdk_threads_enter ();
	gtk_widget_destroy( _window );
	g_object_unref( _window );
	gdk_threads_leave ();

	DEL(_surface);
}

GtkWidget *Window::widget() const {
	return _window;
}

//	Overlays
canvas::VideoOverlay *Window::createOverlayInstance() const {
	return new VideoOverlay( (Window *)this );
}

//	Layer methods
Surface *Window::lockLayer( Canvas *canvas ) {
	if (!_surface) {
		const Size &s = canvas->size();
		_surface = new cairo::Surface( (cairo::Canvas *)canvas, Rect(0,0,s.w,s.h) );
	}

	return _surface;
}

void Window::renderLayer( Surface *surface, const std::vector<Rect> &dirtyRegions ) {
	assert( surface == _surface );
	UNUSED(surface);
	cairo_surface_t *s = _surface->getContent();

	// --user thread
	//	Mark dirty regions
	BOOST_FOREACH( const Rect &r, dirtyRegions ) {
		//	Mark changed region
		cairo_surface_mark_dirty_rectangle(
			s,
			r.x,
			r.y,
			r.w,
			r.h
		);

		//	Mark exposed area
		gtk_widget_queue_draw_area(
			_window,
			r.x,
			r.y,
			r.w,
			r.h
		);
	}
}

void Window::unlockLayer( Surface * /*surface*/ ) {
	//	Unlock surface
}

void Window::draw( GtkWidget *da, const Rect &r ) {
	assert(da);
	if (da == _window && _surface) {
		LDEBUG("gtk::Window", "Draw: rect=(%d,%d,%d,%d)", r.x, r.y, r.w, r.h );

		GdkWindow *win=gtk_widget_get_window(da);
		cairo_t *cr = gdk_cairo_create(win);

		//	set a clip region for the expose event
		cairo_rectangle( cr, r.x, r.y, r.w, r.h );
		cairo_clip( cr );

		cairo_set_operator( cr, CAIRO_OPERATOR_SOURCE );
		cairo_set_source_surface (cr, _surface->getContent(), 0, 0);
		cairo_paint (cr);

		cairo_destroy(cr);
	}
}

void Window::updateWindow( GdkEvent *event ) {
	LTRACE( "gtk::Window", "Update main window properties: type=%d\n", event->type );

	const std::vector<canvas::VideoOverlayPtr> &ovs = overlays();
	BOOST_FOREACH( canvas::VideoOverlay *tmp, ovs ) {
		VideoOverlay *vo = dynamic_cast<VideoOverlay *>(tmp);
		vo->onMainChanged( event );
	}
}

}
}
