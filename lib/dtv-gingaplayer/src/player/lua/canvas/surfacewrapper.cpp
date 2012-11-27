#include "surfacewrapper.h"
#include <canvas/surface.h>
#include <util/mcr.h>

namespace player {
namespace mcanvas {

SurfaceWrapper::SurfaceWrapper( canvas::Surface *surface, bool isPrimary )
	: _surface(surface)
{
	_isPrimary = isPrimary;
	_flipH = false;
	_flipV = false;
	_scaledSize = _surface->getSize();
	_rotation = 0;
}

SurfaceWrapper::~SurfaceWrapper()
{
	if (!_isPrimary) {
		canvas::Surface::destroy( _surface );
	}
}

canvas::Surface *SurfaceWrapper::surface() {
	return _surface;
}

void SurfaceWrapper::setFlip( bool horizontal, bool vertical ) {
	_flipH = horizontal;
	_flipV = vertical;
}

bool SurfaceWrapper::isFlippedH() const {
	return _flipH;
}

bool SurfaceWrapper::isFlippedV() const {
	return _flipV;
}

void SurfaceWrapper::setScaledSize( const canvas::Size &size ) {
	_scaledSize = size;
}

canvas::Size SurfaceWrapper::getScaledSize() const {
	return _scaledSize;
}

void SurfaceWrapper::replaceSurface( canvas::Surface *newSurface ) {
	canvas::Surface::destroy(_surface);
	_surface = newSurface;
	_scaledSize = _surface->getSize();
}

bool SurfaceWrapper::needScale() const {
	return _flipH || _flipV || (_surface->getSize() != _scaledSize);
}

void SurfaceWrapper::rotation( int degrees ) {
	_rotation = degrees;
}

int SurfaceWrapper::rotation() const {
	return _rotation;
}

bool SurfaceWrapper::isPrimary() const {
	return _isPrimary;
}

}
}
