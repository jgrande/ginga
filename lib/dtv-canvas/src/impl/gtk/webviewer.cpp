#include "webviewer.h"
#include "../../surface.h"
#include "../../canvas.h"
#include "../../size.h"
#include "../../system.h"
#include <util/log.h>
#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include <webkit/webkit.h>
#include <boost/bind.hpp>
#include <exception>
#include <stdexcept>
#include <assert.h>

#define TIME_WAIT_RENDER  300

namespace canvas {
namespace cairo {
namespace impl {

void gdk_cairo_set_source_pixbuf (
	cairo_t         *cr,
	const GdkPixbuf *pixbuf,
	double           pixbuf_x,
	double           pixbuf_y);
}
}
}

namespace canvas {
namespace gtk {

static gboolean timeoutCallback(gpointer user_data){
	WebViewer *web = (WebViewer *)user_data;
	assert(web);
	web->onFinished();
	return false;
}

static void on_finished(
	WebKitWebView */*view*/,
	WebKitWebFrame */*frame*/,
	gpointer user_data)
{
	g_timeout_add( TIME_WAIT_RENDER, &timeoutCallback, user_data);
}

WebViewer::WebViewer( System *sys, Surface *surface )
	: canvas::WebViewer(surface), _sys(sys)
{
	_view = NULL;
	_window = NULL;
}

WebViewer::~WebViewer( void )
{
	stopPage();
}

void WebViewer::onResized() {
	const Size &s = this->surface()->getSize();
	gtk_widget_set_size_request ( _view, s.w, s.h );
}

void WebViewer::onFinished() {
	canvas::ImageData img;
	cairo_surface_t *surface;
	cairo_t *cr;

	LDEBUG( "WebViewer", "Render page" );

	//	Do screenshot
	GdkPixbuf *pixbuf=gtk_offscreen_window_get_pixbuf ((GtkOffscreenWindow *)_window);
	if (!pixbuf) {
		LWARN( "WebViewer", "Cannot create offscreen image" );
	}
	
	int width = gdk_pixbuf_get_width(pixbuf);
	int height = gdk_pixbuf_get_height(pixbuf);

	//	Create surface
	surface = cairo_image_surface_create( CAIRO_FORMAT_ARGB32, width, height );
	if (cairo_surface_status(surface) != CAIRO_STATUS_SUCCESS) {
		LERROR("WebViewer", "Cannot create cairo surface!");
		return;
	}

	//	Create context
	cr = cairo_create (surface);
	if (cairo_status(cr) != CAIRO_STATUS_SUCCESS) {
		LERROR("WebViewer", "Cannot create cairo context!");
		return;
	}

	//	Setup cairo context
	cairo_set_line_width( cr, 1.0 );
	cairo_set_antialias( cr, CAIRO_ANTIALIAS_NONE );

	//	Paint pixbuf into temporary surface
	cairo::impl::gdk_cairo_set_source_pixbuf( cr, pixbuf, 0, 0 );
	cairo_paint( cr );

	//	Get image data
	cairo_surface_flush(surface);	
	unsigned char *data = cairo_image_surface_get_data(surface);
	int stride = cairo_image_surface_get_stride(surface);

	//	Setup
	memset(&img,0,sizeof(canvas::ImageData));
	img.size = Size(width,height);
	img.length = width*height*4;
	img.data = data;
	img.bitsPerPixel = 32;
	img.bytesPerPixel = 4;
	img.stride = stride;
	img.dataOffset = 0;	

	//	Create surface from data
	canvas::Surface *sur=_sys->canvas()->createSurface( &img );
	if (sur) {
		this->surface()->blit( Point(0,0), sur );
		this->surface()->flush();
		_sys->canvas()->destroy( sur );
	}

	//	Cleanup
	g_object_unref( pixbuf );
	cairo_destroy(cr);
	cairo_surface_destroy (surface);
	runCallbackLoadFinished();
}

void WebViewer::stopPage() {
	if (_view) {
		LINFO("WebViewer", "Stop page");
		webkit_web_view_stop_loading( WEBKIT_WEB_VIEW(_view) );
		
		//	Destroy widgets
		gtk_widget_destroy(_view);
		_view = NULL;
		
		gtk_widget_destroy(_window);
		_window = NULL;
	}
}

bool WebViewer::load( const std::string &file ) {
	const Size &s = surface()->getSize();

	LINFO("WebViewer", "Load page: url=%s, width=%d, height=%d",
		file.c_str(), s.w, s.h);
	
	stopPage();
	
	//	Create container
	_window = gtk_offscreen_window_new ();
	if (!_window) {
		LERROR("WebViewer", "Cannot create gtk window!");
		gdk_threads_leave ();
		return false;
	}

	//	Create webkit
	_view = webkit_web_view_new ();
	if (!_view) {
		LERROR("WebViewer", "Cannot create gtk webkit webview!");
		gdk_threads_leave ();		
		return false;
	}

	//	Setup webkit
	webkit_web_view_set_full_content_zoom( WEBKIT_WEB_VIEW (_view), TRUE );
	webkit_web_view_set_transparent( WEBKIT_WEB_VIEW (_view), TRUE );

	//	Load url
	webkit_web_view_load_uri (WEBKIT_WEB_VIEW (_view), file.c_str() );
	
	//	Add webkit to container
	gtk_widget_set_size_request ( _view, s.w, s.h );
	gtk_container_add (GTK_CONTAINER (_window), _view);
	gtk_widget_show_all (_window);

	//	Setup callbacks
	g_signal_connect (_view, "load-finished", G_CALLBACK(on_finished), this );
	return true;
}

void WebViewer::stop() {
	stopPage();
}

void WebViewer::draw() {
	if(_view){
			on_finished(NULL, NULL, this);
	}
}

}
}
