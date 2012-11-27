#pragma once

#include "../../surface.h"
#include <pango/pangocairo.h>


typedef struct _cairo cairo_t;
typedef struct _cairo_surface cairo_surface_t;
typedef struct _GdkPixbuf GdkPixbuf;
typedef enum _cairo_operator cairo_operator_t;

namespace canvas {
namespace cairo {

class Canvas;

class Surface : public canvas::Surface {
public:
	Surface( Canvas *canvas, ImageData *img );	
	Surface( Canvas *canvas, const Rect &rect );
	Surface( Canvas *canvas, const std::string &file );
	virtual ~Surface();

	virtual canvas::Canvas *canvas() const;

	virtual Size getSize() const;

	virtual bool getClip( Rect &rect );

	virtual int fontAscent();
	virtual int fontDescent();

	virtual bool setOpacity( util::BYTE alpha );
	virtual util::BYTE getOpacity() const;

	float alpha() const;

	virtual bool saveAsImage( const std::string &file );
	cairo_surface_t *getContent();

protected:
	cairo_t *getContext();

	//	Aux fonts
	void freeFont();
	void loadFont();
	PangoFont *currentFont();
	void loadLayout();
	PangoLayout *currentLayout();

	virtual bool applyFont();
	void init();
	virtual void setClipImpl( const Rect &rect );

	virtual void setCompositionModeImpl( composition::mode mode );

	virtual void drawLineImpl( int x1, int y1, int x2, int y2 );

	virtual void drawRectImpl( const Rect &rect );
	virtual void fillRectImpl( const Rect &rect );

	virtual void drawRoundRectImpl( const Rect &rect, int arcW, int arcH );
	virtual void fillRoundRectImpl( const Rect &rect, int arcW, int arcH );

	// DrawPolygon helper
	void drawLineTo( const Point &lp, const Point &np );
	void drawRelLineTo( const Point &lp, const Point &np );

	virtual void drawPolygonImpl( const std::vector<Point>& vertices, bool closed );
	virtual void fillPolygonImpl( const std::vector<Point>& vertices );

	virtual void drawEllipseImpl( const Point &center, int rw, int rh, int angStart, int angStop );
	virtual void fillEllipseImpl( const Point &center, int rw, int rh, int angStart, int angStop );
    
	virtual void blitImpl( const Point &target, canvas::Surface *srcSurface, const Rect &source );
	virtual void scaleImpl( const Rect &targetRect, canvas::Surface *srcSurface, const Rect &sourceRect, bool flipw=false, bool fliph=false );
	virtual void resizeImpl( const Size &size, bool scaleContent=false );

	virtual canvas::Surface *rotateImpl( int degrees );

	virtual util::DWORD getPixel( const Point &pos );
	virtual void getPixelColorImpl( const Point &pos, Color &color );
	virtual void setPixelColorImpl( const Point &pos, const Color &color );

	virtual void drawTextImpl( const Point &pos, const std::string &text, int ascent );
	virtual void drawTextImpl( const Rect &rect, const std::string &text, Alignment alignment=alignment::None, int spacing=0 );
	virtual void measureTextImpl( const std::string &text, Size &size );

private:
	Canvas *_canvas;
	cairo_t *_cr;
	cairo_surface_t *_surface;
	cairo_operator_t _op;
	float _alpha;
	PangoFont *_pangoFont;
	PangoLayout* _pangoLayout;
};

}
}
	
