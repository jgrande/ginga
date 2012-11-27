#include "surface.h"
#include "rect.h"
#include "canvas.h"
#include "system.h"
#include <util/log.h>
#include <assert.h>

namespace canvas {

void Surface::destroy( Surface *s ) {
	Canvas *canvas = s->canvas();
	canvas->destroy( s );
}

Surface::Surface( const Point &pos )
	: _pos(pos)
{
	_visible = true;
	_zIndex = 1;
	_dirty = false;
	_autoFlush = false;
	_mode = composition::source_over;
	_flushMode = composition::source_over;
	_encoding = charset::ISO_8859_1;
}

Surface::Surface()
{
	_visible = true;
	_zIndex = 1;
	_dirty = false;
	_autoFlush = false;
	_mode = composition::source_over;
	_flushMode = composition::source_over;	
	_encoding = charset::ISO_8859_1;
}

Surface::~Surface()
{
}

void Surface::markDirtySurface( const Rect &rect ) {
    const Point &point=getLocation();
    const Size &size=getSize();
    Rect copy;
    copy.x = point.x + rect.x;
    copy.y = point.y + rect.y;
    copy.w = std::min(std::max(size.w-rect.x,0), rect.w);
    copy.h = std::min(std::max(size.h-rect.y,0), rect.h);
    markDirty( copy );
}

Surface *Surface::createSimilar( const Rect &rect ) {
	Surface *tmp = canvas()->createSurface( rect );
	if (tmp) {
		tmp->setVisible( _visible );
		tmp->setZIndex( _zIndex );
		tmp->autoFlush( _autoFlush );
		tmp->setFont( _font );
		tmp->setColor( _color );
		tmp->setCompositionMode( _mode );
		tmp->flushCompositionMode( _flushMode );
		tmp->setCharsetEncoding( _encoding );
		tmp->markDirty();
	}
	return tmp;
}

const Font &Surface::getFont() const {
	return _font;
}

void Surface::setDefaultFont() {
	setFont( Font() );
}

bool Surface::setFont( const Font &font ) {
	_font = font;
	return applyFont();
}

/****************************** Clip functions ********************************/

bool Surface::setClip( const Rect &rect ) {
    bool check=true;

    check &= pointInBounds( canvas::Point(rect.x, rect.y) );
    check &= pointInBounds( canvas::Point(rect.x+rect.w-1, rect.y+rect.h-1) );
    check &= ( rect.w>0 && rect.h>0 );

    if (check) {
        setClipImpl( rect );
    } else {
        LWARN("Surface", "setClip fail. Invalid bounds rect(x=%d y=%d w=%d h=%d)", rect.x, rect.y, rect.w, rect.h);
    }
    return check;
}

/****************************** Line functions ********************************/

bool Surface::drawLine( int x1, int y1, int x2, int y2 ) {
    bool check=true;

    check &= pointInBounds( canvas::Point(x1, y1) );
    check &= pointInBounds( canvas::Point(x2, y2) );

    if (check) {
        drawLineImpl( x1, y1, x2, y2 );
        int min_x = std::min(x1, x2);
        int min_y = std::min(y1, y2);
        int max_x = std::max(x1, x2);
        int max_y = std::max(y1, y2);

        markDirtySurface( canvas::Rect( min_x, min_y, max_x-min_x+1, max_y-min_y+1 ) );
    } else {
        LWARN("Surface", "drawLine fail. Invalid bounds (x1=%d y1=%d) (x2=%d y2=%d)", x1, y1, x2, y2);
    }

    return check;
}

/****************************** Rect functions ********************************/

bool Surface::drawRect( const Rect &rect ) {
    bool check=true;

    check &= pointInBounds( canvas::Point(rect.x, rect.y) );
    check &= pointInBounds( canvas::Point(rect.x+rect.w-1, rect.y+rect.h-1) );
    check &= (rect.w>=0 && rect.h>=0);

    if (check) {
        if (rect.w>0 && rect.h>0) {
            drawRectImpl(rect);
            markDirtySurface( rect );
        }
    } else {
        LWARN("Surface", "drawRect fail. Invalid bounds rect(x=%d y=%d w=%d h=%d)", rect.x, rect.y, rect.w, rect.h);
    }

    return check;
}

bool Surface::fillRect( const Rect &rect ) {
    bool check=true;

    check &= pointInBounds( canvas::Point(rect.x, rect.y) );
    check &= pointInBounds( canvas::Point(rect.x+rect.w-1, rect.y+rect.h-1) );
    check &= (rect.w>=0 && rect.h>=0);

    if (check) {
        if (rect.w>0 && rect.h>0) {
            fillRectImpl( rect );
            markDirtySurface( rect );
        }
    } else {
        LWARN("Surface", "fillRect fail. Invalid bounds rect(x=%d y=%d w=%d h=%d)", rect.x, rect.y, rect.w, rect.h);
    }

    return check;
}

/*************************** RoundRect functions ******************************/

bool Surface::drawRoundRect( const Rect &rect, int arcW, int arcH ) {
    bool check=true;

    check &= pointInBounds( canvas::Point(rect.x, rect.y) );
    check &= pointInBounds( canvas::Point(rect.x+rect.w-1, rect.y+rect.h-1) );
    check &= (rect.w>=0 && rect.h>=0);
    check &= (arcW > -1 && arcH > -1);

    if (check) {
        if (rect.w>0 && rect.h>0) {
            if (arcW==0 && arcH==0) {
                drawRectImpl( rect );
            } else {
                drawRoundRectImpl(rect, arcW, arcH);
            }
            markDirtySurface( rect );
        }
    } else {
        LWARN("Surface", "drawRoundRect fail. Invalid bounds rect(x=%d y=%d w=%d h=%d, arcW=%d, arcH=%d)", rect.x, rect.y, rect.w, rect.h, arcW, arcH);
    }

    return check;
}

bool Surface::fillRoundRect( const Rect &rect, int arcW, int arcH ) {
    bool check=true;

    check &= pointInBounds( canvas::Point(rect.x, rect.y) );
    check &= pointInBounds( canvas::Point(rect.x+rect.w-1, rect.y+rect.h-1) );
    check &= (rect.w>=0 && rect.h>=0);
    check &= (arcW > -1 && arcH > -1);

    if (check) {
        if (rect.w>0 && rect.h>0) {
            if (arcW==0 && arcH==0) {
                fillRectImpl( rect );
            } else {
                fillRoundRectImpl(rect, arcW, arcH);
            }
            markDirtySurface( rect );
        }
    } else {
	    LWARN("Surface", "fillRoundRect fail. Invalid bounds rect(x=%d y=%d w=%d h=%d, arcW=%d, arcH=%d)",
		    rect.x, rect.y, rect.w, rect.h, arcW, arcH);
    }

    return check;
}

/**************************** Polygon functions ******************************/

bool Surface::drawPolygon( const std::vector<Point>& vertices, bool closed/*=true*/ ) {
    bool check=true;

    check &= vertices.size()>2;

    canvas::Size size = getSize();
    int minX = size.w;
    int minY = size.h;
    int maxX = 0;
    int maxY = 0;
    for(size_t i=0; i<vertices.size() && check; ++i) {
        const Point& p = vertices[i];
        check &= pointInBounds(p);

        if (p.x < minX) {
            minX = p.x;
        }
        if (p.x > maxX) {
            maxX = p.x;
        }
        if (p.y < minY) {
            minY = p.y;
        }
        if (p.y > maxY) {
            maxY = p.y;
        }
    }

    if (check) {
        drawPolygonImpl( vertices, closed );
        markDirtySurface( canvas::Rect(minX, minY, maxX - minX + 1, maxY - minY + 1) );
    } else {
        LWARN("Surface", "drawPolygon fail. Invalid vertices");
    }
    return check;
}

bool Surface::fillPolygon( const std::vector<Point>& vertices ) {
    bool check=true;

    check &= vertices.size()>2;

    canvas::Size size = getSize();
    int minX = size.w;
    int minY = size.h;
    int maxX = 0;
    int maxY = 0;
    for(size_t i=0; i<vertices.size() && check; ++i) {
        const Point& p = vertices[i];
        check &= pointInBounds(p);

        if (p.x < minX) {
            minX = p.x;
        }
        if (p.x > maxX) {
            maxX = p.x;
        }
        if (p.y < minY) {
            minY = p.y;
        }
        if (p.y > maxY) {
            maxY = p.y;
        }
    }

    if (check) {
        fillPolygonImpl( vertices );
        markDirtySurface( canvas::Rect(minX, minY, maxX - minX + 1, maxY - minY + 1) );
    } else {
        LWARN("Surface", "fillPolygon fail. Invalid vertices");
    }
    return check;
}

/**************************** Ellipse functions ******************************/

bool Surface::drawEllipse( const Point &center, int rw, int rh, int angStart, int angStop ) {
    bool check=true;

    check &= pointInBounds( canvas::Point(center.x - rw, center.y) );
    check &= pointInBounds( canvas::Point(center.x + rw, center.y) );
    check &= pointInBounds( canvas::Point(center.x, center.y - rh) );
    check &= pointInBounds( canvas::Point(center.x, center.y + rh) );

    if (check) {
        if (rw>0 && rh>0) {
            drawEllipseImpl(center, rw, rh, angStart, angStop);
            markDirtySurface(canvas::Rect(center.x - rw, center.y - rh, rw*2+1, rh*2+1));
        }
    } else {
        LWARN("Surface", "drawEllipse fail. Invalid bounds center(x=%d y=%d) rw=%d rh=%d angStart=%d angStop=%d", center.x, center.y, rw, rh, angStart, angStop);
    }
    return check;
}

bool Surface::fillEllipse( const Point &center, int rw, int rh, int angStart, int angStop ) {
    bool check=true;

    check &= pointInBounds( canvas::Point(center.x - rw, center.y) );
    check &= pointInBounds( canvas::Point(center.x + rw, center.y) );
    check &= pointInBounds( canvas::Point(center.x, center.y - rh) );
    check &= pointInBounds( canvas::Point(center.x, center.y + rh) );

    if (check) {
        if (rw>0 && rh>0) {
            fillEllipseImpl(center, rw, rh, angStart, angStop);
            markDirtySurface(canvas::Rect(center.x - rw, center.y - rh, rw*2+1, rh*2+1));
        }
    } else {
        LWARN("Surface", "fillEllipse fail. Invalid bounds center(x=%d y=%d) rw=%d rh=%d angStart=%d angStop=%d", center.x, center.y, rw, rh, angStart, angStop);
    }
    return check;
}

/****************************** Text functions ********************************/

void Surface::replaceIndent( std::string &line ) {
	size_t current = 0;
	size_t idx = line.find('\t');
	while (idx != std::string::npos) {
		line.replace(idx, 1, 4, ' ');
		current = idx + 1;
		idx = line.find('\t', current);
	}
}

void Surface::findLines( const std::string &text, std::vector<std::string> &lines ) {
	std::string line;
	size_t current = 0;
	size_t idx = text.find('\n');
	while (idx!=std::string::npos) {
		if (idx==current) {
			line = "";
			current++;
		} else {
			line = text.substr(current, idx-current);
			replaceIndent(line);
			current = idx + 1;
		}
		lines.push_back(line);
		idx = text.find('\n', current);
	}
	line = text.substr(current);
	replaceIndent(line);
	lines.push_back(line);
}

bool Surface::drawText( const Point &pos, const std::string &text ) {
    bool check=true;
    Size size;
    int ascent = fontAscent();
    int descent = fontDescent();

    check &= measureText(text, size);
    check &= pointInBounds(canvas::Point( pos.x, pos.y-ascent+1));
    check &= pointInBounds(canvas::Point(std::max(pos.x+size.w-1,0), pos.y+descent-1));

    if (check) {
        if (text.length()>0) {
            drawTextImpl(pos, text, ascent );
            markDirtySurface(canvas::Rect(pos.x, pos.y-ascent+1, size.w, size.h ));
        }
    } else {
        LWARN("Surface", "drawText fail. Invalid bounds pos(x=%d y=%d) ascent=%d descent=%d)", pos.x, pos.y, ascent, descent);
    }
    return check;
}

bool Surface::drawText( const Rect &rect, const std::string &text, Alignment alignment/*=alignment::None*/, int spacing/*=0*/ ) {
    bool check=true;

    check &= pointInBounds(Point(rect.x, rect.y));
    check &= pointInBounds(Point(std::max(rect.x+rect.w-1,0), std::max(rect.y+rect.h-1,0)));
    //  The rest of the alignments are not yet supported.
    check &= (alignment==canvas::alignment::None);

    if (check) {
        if (text.length()>0) {
            drawTextImpl(rect, text, alignment, spacing);
            markDirtySurface( rect );
        }
    } else {
        LWARN("Surface", "drawText fail. Invalid bounds rect(x=%d y=%d, w=%d, h=%d)", rect.x, rect.y, rect.w, rect.h);
    }
    return check;
}

bool Surface::measureText( const std::string &text, Size &size ) {
    if (text.empty()) {
        size.h = 0;
        size.w = 0;
    } else {
        measureTextImpl(text,size);
    }
    return true;
}

/*********************** Pixel manipulation functions *************************/

bool Surface::getPixelColor( const Point &pos, Color &color ) {
	bool check=true;
	check &= pointInBounds( pos );
	if (check) {
		getPixelColorImpl(pos, color);
	} else {
		LWARN("Surface", "getPixelColor fail. Invalid bounds pos(x=%d y=%d)", pos.x, pos.y);
	}
	return check;
}

bool Surface::setPixelColor( const Point &pos, const Color &color ) {
    bool check=true;

    check &= pointInBounds( pos );
    if (check) {
        setPixelColorImpl(pos, color);
        canvas::Rect rect(pos.x, pos.y, 1, 1);
        markDirtySurface(rect);
    } else {
        LWARN("Surface", "setPixelColor fail. Invalid bounds pos(x=%d y=%d)", pos.x, pos.y);
    }
    return check;
}

void Surface::flush() {
	if (_autoFlush) {
		canvas()->flush();
	}
}

void Surface::autoFlush( bool inCanvasFlush ) {
	_autoFlush=inCanvasFlush;
	setAutoFlushImpl( inCanvasFlush );
	markDirty();
}

void Surface::setAutoFlushImpl( bool /*inCanvasFlush*/ ) {
}

bool Surface::autoFlush() const {
	return _autoFlush;
}

void Surface::flushCompositionMode( composition::mode mode ) {
	_flushMode = mode;
}

composition::mode Surface::flushCompositionMode() {
	return _flushMode;
}

void Surface::markDirty() {
	Rect dirty = getBounds();
	markDirty( dirty );
}

void Surface::markDirty( const Rect &rect ) {
	if (_autoFlush) {
		markDirtyImpl( rect );
		canvas()->invalidateRegion( rect );
		_dirty=true;
	}
}

void Surface::markDirtyImpl( const Rect &/*rect*/ ) {
}

void Surface::clearDirty() {
	_dirty = false;
}

void Surface::invalidateRegion( const Rect &rect ) {
	if (_autoFlush && !_dirty) {
		Rect bounds = getBounds();
		if (rect.intersects( bounds )) {
			_dirty=true;
		}
	}
}

bool Surface::getDirtyRegion( const Rect &dirtyRegion, Rect &blitRect ) {
	Rect bounds = getBounds();
	return dirtyRegion.intersection( bounds, blitRect );
}

bool Surface::isDirty() const {
	return _dirty;
}

void Surface::setZIndex( int zIndex ) {
	if (_zIndex != zIndex) {
		_zIndex = zIndex;
		setZIndexImpl( zIndex );
		markDirty();
	}
}

void Surface::setZIndexImpl( int /*zIndex*/ ) {
}

int Surface::getZIndex() const {
	return _zIndex;
}

void Surface::setColor( const Color &color ) {
	_color = color;
	setColorImpl( _color );
}

void Surface::setColorImpl( Color &/*color*/ ) {
}

const Color &Surface::getColor() const {
    return _color;
}

bool Surface::clear() {
	Size size = getSize();
	Rect bounds(0,0,size.w,size.h);
	return clear( bounds );
}

bool Surface::clear( const Rect &rect ) {
	bool check=true;

	check &= pointInBounds( Point(rect.x, rect.y) );
	check &= pointInBounds( Point(rect.x+rect.w-1, rect.y+rect.h-1) );
	check &= (rect.w>0 && rect.h>0);

	if (check) {
		composition::mode oldMode = getCompositionMode();
		setCompositionMode(composition::clear);
		fillRectImpl(rect);
		setCompositionMode(oldMode);
		markDirtySurface( rect );
	} else {
		LWARN("Surface", "clear fail. Invalid bounds rect(x=%d y=%d w=%d h=%d)", rect.x, rect.y, rect.w, rect.h);
	}
	return check;
}

void Surface::setVisible( bool visible ) {
	if (visible != _visible) {
		setVisibleImpl( visible );
		markDirty();
	}
	_visible = visible;
}

void Surface::setVisibleImpl( bool /*visible*/ ) {
}

bool Surface::isVisible() const {
	return _visible;
}

void Surface::setLocation( const Point &point ) {
	markDirty();
	_pos.x = point.x;
	_pos.y = point.y;
	setLocationImpl( point );
	markDirty();
}

void Surface::setLocationImpl( const Point &/*point*/ ) {
}

const Point &Surface::getLocation() const {
	return _pos;
}

Rect Surface::getBounds() const {
	Point pos = getLocation();
	Size size = getSize();
	Rect bounds(pos.x, pos.y, size.w, size.h);
	return bounds;
}

bool Surface::equalsImage( const std::string &file ) {
	Surface* image = canvas()->createSurfaceFromPath( file );

	if (!image) {
		return false;
	}
	Size s_size = getSize();
	Size i_size = image->getSize();

	if (s_size.w != i_size.w || s_size.h != i_size.h) {
		canvas()->destroy( image );
		return false;
	} else {
		for (int i = 0; i < s_size.w; ++i) {
			for (int j = 0; j < s_size.h; ++j) {
				if (!comparePixels(Point(i,j), image)) {
					canvas()->destroy( image );
					return false;
				}
			}
		}
	}
	canvas()->destroy( image );
	return true;
}

#define THRESHOLD 20
bool Surface::comparePixels( const Point &pos, Surface *image ) {
	util::DWORD p1, p2;
	bool check=true;

	p1 = getPixel(pos);
	p2 = image->getPixel(pos);
	if (p1!=p2) {
		canvas::Color c1, c2;
		getPixelColor(pos, c1);
		image->getPixelColor(pos, c2);
		if (!c1.equals(c2, THRESHOLD ) ) {
			LINFO("Surface", "Difference found in pixel (%d, %d): s_color=(%d,%d,%d,%d), i_color=(%d,%d,%d,%d).",
				pos.x, pos.y, c1.r, c1.g, c1.b, c1.alpha, c2.r, c2.g, c2.b, c2.alpha );
			check=false;
		}
	}
	return check;
}

bool Surface::pointInBounds( const Point &point ) const {
	Size size = getSize();
	bool check_x = point.x > -1 && point.x < size.w;
	bool check_y = point.y > -1 && point.y < size.h;
	return check_x && check_y;
}

bool Surface::blit( const Point &targetPoint, Surface *srcSurface ) {
	const Size &s=srcSurface->getSize();
	Rect srcRect(0,0,s.w,s.h);
	return blit( targetPoint, srcSurface, srcRect );
}

bool Surface::blit( const Point &targetPoint, Surface *srcSurface, const Rect &source ) {
	bool check=true;

	check &= (source.w>=0 && source.h>=0);
	check &= srcSurface->pointInBounds( canvas::Point(source.x, source.y) );

	int source_x2 = source.x+(source.w?source.w-1:0);
	int source_y2 = source.y+(source.h?source.h-1:0);
	check &= srcSurface->pointInBounds( canvas::Point(source_x2, source_y2) );

	if (check) {
		blitImpl(targetPoint, srcSurface, source);
		markDirtySurface( Rect( targetPoint.x, targetPoint.y, source.w, source.h ) );
	} else {
		const Rect &bounds=getBounds();
		LWARN("Surface", "blit fail. Invalid bounds: bounds=(%d,%d,%d,%d), targetPoint=(x=%d y=%d) source=(x=%d y=%d w=%d h=%d)",
			bounds.x, bounds.y, bounds.w, bounds.h,
			targetPoint.x, targetPoint.y,
			source.x, source.y, source.w, source.h);
	}
	return check;
}

bool Surface::scale( const Rect &targetRect, Surface *srcSurface, bool flipw /*=false*/, bool fliph /*=false*/ ) {
	const Size &s=srcSurface->getSize();
	Rect srcRect(0,0,s.w,s.h);
	return scale( targetRect, srcSurface, srcRect, flipw, fliph );
}

bool Surface::scale( const Rect &targetRect, Surface *srcSurface, const Rect &source, bool flipw /*=false*/, bool fliph /*=false*/ ) {
	bool check=true;

	check &= (source.w>0 && source.h>0);
	check &= srcSurface->pointInBounds( canvas::Point(source.x, source.y) );
	
	int source_x2 = source.x+(source.w?source.w-1:0);
	int source_y2 = source.y+(source.h?source.h-1:0);
	check &= srcSurface->pointInBounds( canvas::Point(source_x2, source_y2) );

	check &= (targetRect.w>0 && targetRect.h>0);
	check &= pointInBounds( canvas::Point(targetRect.x, targetRect.y) );

	source_x2 = targetRect.x+(targetRect.w?targetRect.w-1:0);
	source_y2 = targetRect.y+(targetRect.h?targetRect.h-1:0);
	check &= pointInBounds( canvas::Point(source_x2, source_y2) );

	if (check) {
		scaleImpl( targetRect, srcSurface, source, flipw, fliph );
		markDirtySurface( targetRect );
	} else {
		const Rect &bounds=getBounds();
		LWARN("Surface", "scale fail. Invalid bounds: bounds=(%d,%d,%d,%d), target=(%d,%d,%d,%d) source=(%d,%d,%d,%d)",
			bounds.x, bounds.y, bounds.w, bounds.h,
			targetRect.x, targetRect.y, targetRect.w, targetRect.h,
			source.x, source.y, source.w, source.h);
	}
	return check;
}

Surface *Surface::rotate( int degrees ) {
	Surface *newSurface = NULL;
	if ((degrees%90) != 0) {
		LWARN("Surface", "rotate fail. Degrees must be a multiple of 90 (degrees=%d)", degrees);
	} else {
		while (degrees<0) {
			degrees = degrees + 360;
		}
		newSurface = rotateImpl( degrees%360 );
		markDirtySurface( newSurface->getBounds() );
	}
	return newSurface;
}

bool Surface::resize( const Size &size, bool scaleContent/*=false*/ ) {
	bool check = size.w>0 && size.h>0;
	if (check) {
		markDirtySurface(getBounds());
		resizeImpl(size, scaleContent);
		markDirtySurface(getBounds());
	} else {
		LWARN("Surface", "resize fail. New size must be greater than 0. newSize=(%d,%d)", size.w, size.h);
	}
	return check;
}

void Surface::setCompositionMode( composition::mode mode ) {
	switch (mode) {
		case composition::source_over:
		case composition::source:
		case composition::clear:
			_mode = mode;
			setCompositionModeImpl( mode );
			break;
		default:
			LWARN("Surface", "setCompositionMode fail. Composition mode not suported!");
			break;
	}
}

void Surface::setCharsetEncoding( charset::encoding encoding ) {
	switch (encoding) {
		case charset::ISO_8859_1:
			_encoding = encoding;
			setCharsetEncodingImpl( encoding );
			break;
		default:
			LWARN("Surface", "setCharsetEncoding fail. Charset encoding not suported!");
			break;
	}
}

charset::encoding Surface::getCharsetEncoding() const {
	return _encoding;
}

composition::mode Surface::getCompositionMode() {
	return _mode;
}

}
