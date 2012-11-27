#pragma once

#include "../surface.h"

namespace canvas {
namespace dummy {

class Surface : public canvas::Surface {
public:
	Surface( canvas::Canvas *canvas, const Rect &rect );
	Surface( canvas::Canvas *canvas, ImageData *img );
	Surface( canvas::Canvas *canvas, const std::string &file );	
	virtual ~Surface();
	
	virtual canvas::Canvas *canvas() const;
	virtual Size getSize() const;
	virtual bool getClip( Rect &rect );

	virtual int fontAscent();
	virtual int fontDescent();

	virtual bool setOpacity( util::BYTE alpha );
	virtual util::BYTE getOpacity() const;

	virtual bool saveAsImage( const std::string &file );

protected:
	virtual bool applyFont();
	virtual void setClipImpl( const Rect &rect );
	virtual void drawLineImpl( int x1, int y1, int x2, int y2 );
	virtual void drawRectImpl( const Rect &rect );
	virtual void fillRectImpl( const Rect &rect );
	virtual void drawRoundRectImpl( const Rect &rect, int arcW, int arcH );
	virtual void fillRoundRectImpl( const Rect &rect, int arcW, int arcH );
	virtual void drawPolygonImpl( const std::vector<Point>& vertices, bool closed );
	virtual void fillPolygonImpl( const std::vector<Point>& vertices );
	virtual void drawEllipseImpl( const Point &center, int rw, int rh, int angStart, int angStop );
	virtual void fillEllipseImpl( const Point &center, int rw, int rh, int angStart, int angStop );
	virtual void blitImpl( const Point &target, canvas::Surface *srcSurface, const Rect &source );
	virtual void scaleImpl( const Rect &targetRect, canvas::Surface *srcSurface, const Rect &sourceRect, bool flipw=false, bool fliph=false );
	virtual canvas::Surface *rotateImpl( int degrees );
	virtual void resizeImpl( const Size &size, bool scaleContent=false );
	virtual void getPixelColorImpl( const Point &pos, Color &color );
	virtual void setPixelColorImpl( const Point &pos, const Color &color );
	virtual void drawTextImpl( const Point &pos, const std::string &text, int ascent );
	virtual void drawTextImpl( const Rect &rect, const std::string &text, Alignment alignment=alignment::None, int spacing=0 );
	virtual void measureTextImpl( const std::string &text, Size &size );
	virtual bool comparePixels( const Point &pos, canvas::Surface* image );
	virtual util::DWORD getPixel( const Point &pos );

private:
	canvas::Canvas *_canvas;
	Size _size;
};

}
}
	
