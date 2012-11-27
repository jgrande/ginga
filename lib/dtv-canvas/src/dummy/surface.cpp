#include "surface.h"
#include "../rect.h"
#include <util/log.h>

namespace canvas {
namespace dummy {

Surface::Surface( canvas::Canvas *canvas, const Rect &rect )
	: canvas::Surface( Point(rect.x,rect.y) ), _canvas(canvas), _size(rect.w, rect.h)
{
	LDEBUG("dummy::Surface", "Create: surface=%p", this);
}

Surface::Surface( canvas::Canvas *canvas, const std::string & /*file*/ )
	: canvas::Surface( Point(0,0) ), _canvas(canvas), _size(720,576)
{
	LDEBUG("dummy::Surface", "Create: surface=%p", this);
}

Surface::Surface( canvas::Canvas *canvas, ImageData *img )
	: canvas::Surface( Point(0,0) ), _canvas(canvas), _size(img->size)
{
	LDEBUG("dummy::Surface", "Create: surface=%p", this);
}
	
Surface::~Surface()
{
	LDEBUG("dummy::Surface", "Destroy: surface=%p", this);
}

canvas::Canvas *Surface::canvas() const {
	return _canvas;
}

Size Surface::getSize() const {
	return _size;
}

bool Surface::getClip( Rect & /*rect*/ ) {
	return true;
}

int Surface::fontAscent() {
	return 0;
}

int Surface::fontDescent() {
	return 0;
}

bool Surface::setOpacity( util::BYTE /*alpha*/ ) {
	return true;
}

util::BYTE Surface::getOpacity() const{
	return 1;
}

bool Surface::saveAsImage( const std::string & /*file*/ ) {
	return true;
}

bool Surface::applyFont() {
	return true;
}

void Surface::setClipImpl( const Rect & /*rect*/ ) {
}

void Surface::drawLineImpl( int /*x1*/, int /*y1*/, int /*x2*/, int /*y2*/ ) {
}

void Surface::drawRectImpl( const Rect & /*rect*/ ) {
}

void Surface::fillRectImpl( const Rect & /*rect*/ ) {
}

void Surface::drawRoundRectImpl( const Rect & /*rect*/, int /*arcW*/, int /*arcH*/ ) {
}

void Surface::fillRoundRectImpl( const Rect & /*rect*/, int /*arcW*/, int /*arcH*/ ) {
}

void Surface::drawPolygonImpl( const std::vector<Point>& /*vertices*/, bool /*closed*/ ) {
}

void Surface::fillPolygonImpl( const std::vector<Point>& /*vertices*/ ) {
}

void Surface::drawEllipseImpl( const Point & /*center*/, int /*rw*/, int /*rh*/, int /*angStart*/, int /*angStop*/ ) {
}

void Surface::fillEllipseImpl( const Point & /*center*/, int /*rw*/, int /*rh*/, int /*angStart*/, int /*angStop*/ ) {
}

void Surface::blitImpl( const Point & /*target*/, canvas::Surface * /*srcSurface*/, const Rect & /*source*/ ) {
}

void Surface::scaleImpl( const Rect & /*targetRect*/, canvas::Surface * /*srcSurface*/, const Rect & /*sourceRect*/, bool /*flipw=false*/, bool /*fliph=false*/ ) {
}

canvas::Surface *Surface::rotateImpl( int /*degrees*/ ) {
	return NULL;
}

void Surface::getPixelColorImpl( const Point & /*pos*/, Color &color ) {
	color = Color();
}

void Surface::setPixelColorImpl( const Point & /*pos*/, const Color & /*color*/ ) {
}

void Surface::drawTextImpl( const Point & /*pos*/, const std::string & /*text*/, int /*ascent*/ ) {
}

void Surface::drawTextImpl( const Rect & /*rect*/, const std::string & /*text*/, Alignment /*alignment=alignment::None*/, int /*spacing=0*/ ) {
}

void Surface::measureTextImpl( const std::string & /*text*/, Size &size ) {
	size = Size(10,10);
}

bool Surface::comparePixels( const Point &/*pos*/, canvas::Surface* /*image*/ ) {
	return true;
}

util::DWORD Surface::getPixel( const Point & /*pos*/ ) {
	return 0;
}

void Surface::resizeImpl( const Size &/*size*/, bool /*scaleContent=false*/ ) {
}

}
}
	
