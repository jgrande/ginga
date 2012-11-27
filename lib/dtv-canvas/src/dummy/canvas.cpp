#include "canvas.h"
#include "surface.h"
#include "../size.h"

namespace canvas {
namespace dummy {

Canvas::Canvas()
{
}

Canvas::~Canvas( void )
{
}

std::string Canvas::name() {
	return "dummy";
}

canvas::Surface *Canvas::createSurfaceImpl( ImageData *img ) {
	return new Surface(this,img);	
}

canvas::Surface *Canvas::createSurfaceImpl( const Rect &rect ) {
	return new Surface(this,rect);
}

canvas::Surface *Canvas::createSurfaceImpl( const std::string &file ) {
	return new Surface(this,file);
}

}
}

