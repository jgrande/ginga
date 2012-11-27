#include "window.h"
#include "videooverlay.h"
#include "dummy/window.h"
#include "generated/config.h"
#if SYS_WINDOW_USE_FB
#	include "impl/fb/window.h"
#endif
#if CANVAS_USE_REMOTE
#include "remote/window.h"
#endif
#include <util/log.h>
#include <util/cfg/configregistrator.h>
	
namespace canvas {

REGISTER_INIT_CONFIG( gui_window ) {
	root().addNode( "window" )
#if SYS_SYSTEM_USE_GTK
	.addValue( "use", "Window to instance", std::string("gtk") )
#else
	.addValue( "use", "Window to instance", std::string("dummy") )
#endif
	.addValue( "title", "Window title", std::string("Dummy") )
	.addValue( "fullscreen", "Window fullscreen option", false )
	.addNode( "size" )
		.addValue( "width", "Window width", 720 )
		.addValue( "height", "Window height", 576 );
}

Window *Window::create() {
	std::string use = util::cfg::getValue<std::string>("gui.window.use");
	LDEBUG("Window", "Creating window: use=%s", use.c_str() );
	
#if SYS_WINDOW_USE_FB
	if (use == "fb") {
		return new fb::Window();
	}
#endif
#if CANVAS_USE_REMOTE
	if (use == "remote") {
		return new remote::Window();
	}
#endif

	return new dummy::Window();
}

Window::Window()
{
	util::cfg::PropertyNode &root = util::cfg::get("gui.window");
	_title = root.get<std::string>("title");
	_isFullScreen = root.get<bool>("fullscreen");
	_size.h = root.get<int>("size.height");
	_size.w = root.get<int>("size.width");

	if (_isFullScreen ) {
		LINFO("Window", "Creating display in fullscreen");
	} else {
		LINFO("Window", "Creating display: size=(%d,%d)", _size.w, _size.h );
	}
}

Window::~Window()
{
	if (_overlays.size()) {
		LWARN("Window", "not all video overlays destroyed: size=%d", _overlays.size() );
	}
}

//	Initialization
bool Window::initialize() {
	return true;
}

void Window::finalize() {
}

const std::string &Window::title() const {
	return _title;
}

const Size &Window::size() const {
	return _size;
}

void Window::setSize( int width, int height ) {
	_size.w = width;
	_size.h = height;
	LDEBUG("Window", "Size changed: w=%d, h=%d", _size.w, _size.h);
}

//	Overlays
const std::vector<VideoOverlayPtr> &Window::overlays() const {
	return _overlays;
}

VideoOverlay *Window::createOverlayInstance() const {
	return new VideoOverlay();
}

VideoOverlay *Window::createVideoOverlay() {
	VideoOverlay *tmp=createOverlayInstance();
	if (tmp) {
		_overlays.push_back( tmp );
	}
	return tmp;
}

void Window::destoyVideoOverlay( VideoOverlayPtr &ptr ) {
	LDEBUG("Canvas", "Destroy overlay: overlay=%p", ptr );
	assert(ptr);
	std::vector<VideoOverlay *>::iterator it=std::find(
		_overlays.begin(), _overlays.end(), ptr );
	if (it != _overlays.end()) {
		delete (*it);
		_overlays.erase( it );
	}
	ptr = NULL;	
}

//	Mode methods
void Window::setMode() {
	if (_isFullScreen) {
		setFullscreenMode();
	} else {
		setNormalMode();
	}
}

void Window::setFullscreenMode() {}

void Window::setNormalMode() {}

//	Window methods
void Window::redraw( Canvas *canvas ) {
	canvas::Rect r(0,0,_size.w,_size.h);
	redraw( canvas, r );
}

void Window::redraw( Canvas *canvas, const Rect &r ) {
	std::vector<Rect> rects;
	rects.push_back( r );
	Surface *s = lockLayer( canvas );
	if (s) {
		renderLayer( s, rects );
		unlockLayer( s );
	}
}

//	Layer methods
void Window::unlockLayer( Surface * /*surface*/ ) {
}

//	Video methods
int Window::getFormat( char * /*chroma*/, unsigned * /*width*/, unsigned * /*height*/, unsigned * /*pitches*/, unsigned * /*lines*/ ) {
	return 0;
}

void Window::cleanup() {
}

void *Window::allocFrame( void ** /*pixels*/ ) {
	return NULL;
}

void Window::freeFrame( void * /*frame*/ ) {
}

void Window::renderFrame( void * /*frame*/ ) {
}
	
}

