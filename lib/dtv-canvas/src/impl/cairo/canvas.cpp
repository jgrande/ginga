#include "canvas.h"
#include "surface.h"
#include <assert.h>

namespace canvas {
namespace cairo {

Canvas::Canvas()
{
	g_type_init();	
}

Canvas::~Canvas( void )
{
}

std::string Canvas::name() {
	return "cairo";
}

canvas::Surface *Canvas::createSurfaceImpl( ImageData *img ) {
	return new Surface( this, img );
}

canvas::Surface *Canvas::createSurfaceImpl( const Rect &rect ) {
	return new Surface( this, rect );
}

canvas::Surface *Canvas::createSurfaceImpl( const std::string &file ) {
	return new Surface( this, file );	
}

}
}

