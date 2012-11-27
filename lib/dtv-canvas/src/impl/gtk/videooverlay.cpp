#include "videooverlay.h"
#include "window.h"
#include "../../color.h"
#include "../../surface.h"
#include <gtk/gtk.h>
#ifdef GDK_WINDOWING_X11
#include <gdk/gdkx.h>
#endif
#include <util/log.h>

namespace canvas {
namespace gtk {

VideoOverlay::VideoOverlay( Window *win )
{
	_main = win;
	_window = NULL;
	_needMove = true;
}

VideoOverlay::~VideoOverlay( void )
{
	assert(!_window);
}

bool VideoOverlay::initialize( const Rect &rect ) {
	assert(_main);

	LDEBUG("gtk::VideoOverlay", "Initialize");	

	//	Create top level window
	_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated (GTK_WINDOW (_window), FALSE);
	gtk_window_set_resizable (GTK_WINDOW(_window), FALSE);
	gtk_window_set_skip_taskbar_hint( GTK_WINDOW(_window), TRUE );
	gtk_window_set_accept_focus( GTK_WINDOW(_window), FALSE );
	gtk_window_set_destroy_with_parent( GTK_WINDOW(_window), TRUE );

	gtk_widget_realize(_window);

	_rect = rect;
	config();
	
	gtk_widget_show(_window);	

	return true;
}

void VideoOverlay::finalize() {
	LDEBUG("gtk::VideoOverlay", "Stop");
	if (_window) {
		gtk_widget_destroy(_window);
		_window = NULL;
	}
}

bool VideoOverlay::move( const Point &point ) {
	const Size &s = _main->size();
	gint x,y,borderLeft,borderBottom;
	GdkRectangle fRect;

	GdkWindow *window = gtk_widget_get_window(_main->widget()); //	Getting window
	gdk_window_get_origin(window, &x,&y);  //	Parent's left-top screen coordinates
	gdk_window_get_frame_extents( window, &fRect ); //	Getting size and position including decorations


	//Calculating borders
	borderLeft = (fRect.width-s.w)/2;
	borderBottom = fRect.height - (s.h + (y-fRect.y));

	if (_needMove) {
		gtk_window_move( GTK_WINDOW (_main->widget()), fRect.x  ,fRect.y );
	}
	_needMove = !_needMove;

	gtk_window_move( GTK_WINDOW(_window), fRect.x+(fRect.width-s.w)+point.x-borderLeft, fRect.y+(fRect.height-s.h)+point.y-borderBottom );

	_rect = point;
	return true;
}

bool VideoOverlay::resize( const Size &size ) {
	GdkGeometry hints;
	hints.min_width = size.w;
	hints.min_height = size.h;
	hints.width_inc = size.w;
	hints.height_inc = size.h;
	
	GdkWindowHints mask = (GdkWindowHints) (GDK_HINT_RESIZE_INC | GDK_HINT_MIN_SIZE );

	gtk_window_set_geometry_hints (GTK_WINDOW (_window),
		_window,
		&hints,
		mask);

	_rect = size;

	return true;
}

void VideoOverlay::size( Size &size ) {
	gtk_window_get_size( GTK_WINDOW(_window), &size.w, &size.h );
}

bool VideoOverlay::getDescription( VideoDescription &desc ) {
#ifdef _WIN32
	desc = NULL;
#else
	desc.display = GDK_WINDOW_XDISPLAY(gtk_widget_get_window(_window));
	desc.screenID = GDK_SCREEN_XNUMBER(gtk_widget_get_screen(GTK_WIDGET(_window)));
	desc.winID = GDK_WINDOW_XID(gtk_widget_get_window(_window));
#endif
	return true;
}

void VideoOverlay::config() {
	gdk_window_restack(
		gtk_widget_get_window(_window),
		gtk_widget_get_window(_main->widget()),
		FALSE
	);

	{	//	Set position
		Point p(_rect);
		move( p );
	}

	{	//	Set size
		Size s(_rect);
		resize(s);
	}
}

void VideoOverlay::onMainChanged( GdkEvent *event ) {
	if (event->type == GDK_CONFIGURE) {
		config();
	}
	else if (event->type == GDK_UNMAP) {
		gtk_widget_hide( _window );
	}
	else if (event->type == GDK_MAP || event->type == GDK_FOCUS_CHANGE) {
		gtk_widget_show( _window );
		config();
	}
}

}
}

