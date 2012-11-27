#include "dummywebviewer.h"
#include "../color.h"
#include "../rect.h"
#include "../surface.h"
#include <util/log.h>

namespace canvas {
namespace dummy {

WebViewer::WebViewer( Surface *surface )
	: canvas::WebViewer( surface )
{
}

WebViewer::~WebViewer( void )
{
}

bool WebViewer::load( const std::string &file ) {
	LINFO("WebViewer", "load: uri=%s", file.c_str());
	return true;
}

void WebViewer::stop() {
	LINFO("WebViewer", "stop");
}

void WebViewer::draw() {
	const Rect &bounds = surface()->getBounds();
	LDEBUG("WebViewer", "draw: (x=%d,y=%d,w=%d,h=%d)", bounds.x, bounds.y, bounds.w, bounds.h );

	const Color color( 255, 0, 255, 255 );
	surface()->setColor( color );

	surface()->setCompositionMode( composition::source );
	Rect rect(0,0,bounds.w-1,bounds.h-1);
	surface()->fillRect( rect );
	surface()->setCompositionMode( composition::source_over );
}

}
}

