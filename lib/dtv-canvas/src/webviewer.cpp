#include "webviewer.h"
#include "surface.h"
#include "dummy/dummywebviewer.h"
#include <util/log.h>
#include <util/mcr.h>
#include "generated/config.h"
#if SYS_HTML_USE_CEF
#include "impl/cef/webviewer.h"
#endif
#include <assert.h>

namespace canvas {

WebViewer *WebViewer::create( System *sys, Surface *surface ) {
#if SYS_HTML_USE_CEF
	return new cef::WebViewer( sys, surface );
#else
	UNUSED(sys);
	return new dummy::WebViewer( surface );
#endif
}

WebViewer::WebViewer( canvas::Surface *surface )
	: _surface( surface )
{
	_surface->setCompositionMode( composition::source );
}

WebViewer::~WebViewer( void )
{
}

//	Widget
void WebViewer::resize( const Size & /*size*/ ) {
	onResized();	//	TODO: maty
}

void WebViewer::move( const Point & /*point*/ ) {
	onResized();	//	TODO: maty	
}

void WebViewer::onResized() {
	const Size &size = _surface->getSize();
	LDEBUG("WebViewer", "Surface resized: width=%d, height=%d", size.w, size.h);
}

Surface *WebViewer::surface() {
	assert(_surface);
	return _surface;
}

void WebViewer::setCallbackLoadFinished( const Callback &callback ){
	_callbackFinished = callback;
}

void WebViewer::runCallbackLoadFinished(){
	if (_callbackFinished){
		_callbackFinished();
	}
}
}

