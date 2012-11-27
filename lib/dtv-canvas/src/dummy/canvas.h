#pragma once

#include "../canvas.h"

namespace canvas {
namespace dummy {

class Canvas : public canvas::Canvas {
public:
	Canvas();
	virtual ~Canvas();

	virtual std::string name();

protected:
	virtual canvas::Surface *createSurfaceImpl( ImageData *img );
	virtual canvas::Surface *createSurfaceImpl( const Rect &rect );
	virtual canvas::Surface *createSurfaceImpl( const std::string &file );
};

}
}

