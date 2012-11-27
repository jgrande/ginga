#pragma once

#include "../window.h"

namespace canvas {
namespace dummy {

class Surface;

class Window : public canvas::Window {
public:
	Window();
	explicit Window( canvas::Surface * );
	virtual ~Window();

	//	Layer methods
	virtual canvas::Surface *lockLayer( canvas::Canvas *canvas );
	virtual void renderLayer( canvas::Surface *surface, const std::vector<Rect> &dirtyRegions );

private:
	canvas::Surface *_surface;
};
	
}
}

