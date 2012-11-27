#include "window.h"
#include "surface.h"
#include "canvas.h"

namespace canvas {
namespace dummy {

Window::Window()
{
	_surface = NULL;
}

Window::Window( canvas::Surface *surface )
{
	_surface = surface;
}

Window::~Window()
{
	delete _surface;
}
	
//	Layer methods
canvas::Surface *Window::lockLayer( canvas::Canvas *canvas ) {
	if (!_surface) {
		const Size &s = canvas->size();
		_surface = new Surface( canvas, Rect(0,0,s.w,s.h) );
	}
	return _surface;
}

void Window::renderLayer( canvas::Surface * /*surface*/, const std::vector<Rect> & /*dirtyRegions*/ ) {
}
	
}
}

