#pragma once

#include "types.h"
#include "point.h"
#include "color.h"
#include "font.h"
#include "size.h"
#include "rect.h"
#include "alignment.h"
#include <vector>
#include <string>

namespace canvas {

class Surface {
public:
	explicit Surface( const Point &pos );
	virtual ~Surface();

	static void destroy( Surface *s );

	const Font &getFont() const;
	void setDefaultFont();
	bool setFont( const Font &font );

	virtual bool getClip( Rect &rect )=0;
	bool setClip( const Rect &rect );

	bool drawLine( int x1, int y1, int x2, int y2 );

	bool drawRect( const Rect &rect );
	bool fillRect( const Rect &rect );

	bool drawRoundRect( const Rect &rect, int arcW, int arcH );
	bool fillRoundRect( const Rect &rect, int arcW, int arcH );

	bool drawPolygon( const std::vector<Point>& vertices, bool closed=true );
	bool fillPolygon( const std::vector<Point>& vertices );

	bool drawEllipse( const Point &center, int rw, int rh, int angStart, int angStop );
	bool fillEllipse( const Point &center, int rw, int rh, int angStart, int angStop );

	//	Note: The y-position is used as the baseline of the font.
	bool drawText( const Point &pos, const std::string &text );
	//	Note: The y-coordinate of rectangle is used as the top of the font.
	bool drawText( const Rect &rect, const std::string &text, Alignment alignment=alignment::None, int spacing=0 );
	bool measureText( const std::string &text, Size &size );
	virtual int fontAscent()=0;
	virtual int fontDescent()=0;

	bool blit( const Point &targetPoint, Surface *srcSurface );
	bool blit( const Point &targetPoint, Surface *srcSurface, const Rect &sourceRect );

	bool scale( const Rect &targetRect, Surface *srcSurface, bool flipw=false, bool fliph=false );
	bool scale( const Rect &targetRect, Surface *srcSurface, const Rect &sourceRect, bool flipw=false, bool fliph=false );

	Surface *rotate( int degrees );

	bool resize( const Size &size, bool scaleContent=false );

	void setCompositionMode( composition::mode mode );
	composition::mode getCompositionMode();

	void setCharsetEncoding( charset::encoding encoding );
	charset::encoding getCharsetEncoding() const;

	bool getPixelColor( const Point &pos, Color &color );
	bool setPixelColor( const Point &pos, const Color &color );

	virtual bool saveAsImage( const std::string &file )=0;
	virtual bool equalsImage( const std::string &file );

	void flush();
	void autoFlush( bool inCanvasFlush );
	bool autoFlush() const;

	void flushCompositionMode( composition::mode mode );
	composition::mode flushCompositionMode();

	void markDirty();
	void markDirty( const Rect &rect );
	bool isDirty() const;
	void clearDirty();
	bool getDirtyRegion( const Rect &dirtyRegion, Rect &blitRect );
	void invalidateRegion( const Rect &rect );

	void setZIndex( int zIndex );
	int getZIndex() const;

	virtual bool setOpacity( util::BYTE alpha  )=0;
	virtual util::BYTE getOpacity() const=0;

	void setColor( const Color &color );
	const Color &getColor() const;

	bool clear();
	bool clear( const Rect &rect );

	void setVisible( bool visible );
	bool isVisible() const;

	Rect getBounds() const;

	void setLocation( const Point &point );
	const Point &getLocation() const;

	virtual Size getSize() const=0;

	virtual Canvas *canvas() const=0;
	bool pointInBounds( const Point &point ) const;

protected:
	virtual Surface *createSimilar( const Rect &rect );

	void markDirtySurface( const Rect &rect );
	virtual bool applyFont()=0;
	virtual void setLocationImpl( const Point &point );
	virtual void setVisibleImpl( bool visible );
	virtual void setZIndexImpl( int zIndex );
	virtual void setColorImpl( Color &color );
	virtual void setAutoFlushImpl( bool inCanvasFlush );
	virtual void markDirtyImpl( const Rect &rect );
	virtual void setClipImpl( const Rect &rect )=0;

	virtual void drawLineImpl( int x1, int y1, int x2, int y2 )=0;

	virtual void drawRectImpl( const Rect &rect )=0;
	virtual void fillRectImpl( const Rect &rect )=0;

	virtual void drawRoundRectImpl( const Rect &rect, int arcW, int arcH )=0;
	virtual void fillRoundRectImpl( const Rect &rect, int arcW, int arcH )=0;

	virtual void drawPolygonImpl( const std::vector<Point>& vertices, bool closed )=0;
	virtual void fillPolygonImpl( const std::vector<Point>& vertices )=0;

	virtual void drawEllipseImpl( const Point &center, int rw, int rh, int angStart, int angStop )=0;
	virtual void fillEllipseImpl( const Point &center, int rw, int rh, int angStart, int angStop )=0;
	
	virtual void blitImpl( const Point &target, Surface *srcSurface, const Rect &source )=0;
	virtual void scaleImpl( const Rect &targetRect, Surface *srcSurface, const Rect &sourceRect, bool flipw=false, bool fliph=false )=0;

	virtual Surface *rotateImpl( int degrees )=0;
	virtual void resizeImpl( const Size &size, bool scaleContent=false )=0;

	virtual void getPixelColorImpl( const Point &pos, Color &color )=0;
	virtual void setPixelColorImpl( const Point &pos, const Color &color )=0;

	virtual void drawTextImpl( const Point &pos, const std::string &text, int ascent )=0;
	virtual void drawTextImpl( const Rect &rect, const std::string &text, Alignment alignment=alignment::None, int spacing=0 )=0;
	virtual void measureTextImpl( const std::string &text, Size &size )=0;

	// drawText helpers
	void replaceIndent( std::string &line );
	void findLines( const std::string &text, std::vector<std::string> &lines );

	virtual bool comparePixels( const Point &pos, Surface* image );
	virtual util::DWORD getPixel( const Point &pos )=0;

	virtual void setCompositionModeImpl( composition::mode /*mode*/ ) {}

	virtual void setCharsetEncodingImpl( charset::encoding /*encoding*/ ) {}

private:
	int _zIndex;
	bool _visible;
	bool _dirty;
	bool _autoFlush;
	Color _color;
	Point _pos;
	Font _font;
	composition::mode _mode;
	composition::mode _flushMode;	
	charset::encoding _encoding;

	Surface();
};

}
