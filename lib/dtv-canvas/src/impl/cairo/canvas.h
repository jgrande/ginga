#pragma once

#include "../../canvas.h"

typedef struct _cairo cairo_t;
typedef struct _cairo_surface cairo_surface_t;

namespace canvas {

class Window;

namespace cairo {

class Surface;

class Canvas : public canvas::Canvas {
public:
	Canvas();
	virtual ~Canvas( void );

	virtual std::string name();

protected:
	virtual canvas::Surface *createSurfaceImpl( ImageData *img );
	virtual canvas::Surface *createSurfaceImpl( const Rect &rect );
	virtual canvas::Surface *createSurfaceImpl( const std::string &file );
};

}
}

