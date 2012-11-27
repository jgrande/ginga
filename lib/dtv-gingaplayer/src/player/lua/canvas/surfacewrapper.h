#pragma once

#include <canvas/size.h>

namespace canvas {
	class Surface;
}

namespace player {
namespace mcanvas {

class SurfaceWrapper {
public:
	SurfaceWrapper( canvas::Surface *surface, bool isPrimary );
	virtual ~SurfaceWrapper();

	canvas::Surface *surface();

	void setFlip( bool horizontal, bool vertical );
	bool isFlippedH() const;
	bool isFlippedV() const;

	void setScaledSize( const canvas::Size &size );
	canvas::Size getScaledSize() const;

	void replaceSurface( canvas::Surface *newSurface );

	bool needScale() const;

	void rotation( int degrees );
	int rotation() const;

	bool isPrimary() const;

private:
	canvas::Surface *_surface;
	bool _flipH;
	bool _flipV;
	canvas::Size _scaledSize;
	int _rotation;
	bool _isPrimary;

	SurfaceWrapper() {}
};

typedef SurfaceWrapper * SurfaceWrapperPtr;

}
}
