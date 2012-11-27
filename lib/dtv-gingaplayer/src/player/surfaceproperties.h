#pragma once

#include <canvas/point.h>
#include <canvas/size.h>
#include <canvas/rect.h>
#include <canvas/color.h>
#include <boost/function.hpp>
#include <string>

namespace canvas {
	class Canvas;
	class Surface;
}

namespace player {

class Player;

template<typename T> class PropertyImpl;

class SurfaceProperties {
public:
	SurfaceProperties( canvas::Canvas *canvas );
	virtual ~SurfaceProperties( void );

	bool createSurface();
	void destroy();
	void registerProperties( Player *player );

	canvas::Surface *surface() const;

	//	Events
	typedef boost::function<void (const canvas::Size &)> OnSizeChanged;
	void onSizeChanged( const OnSizeChanged &callback );

	typedef boost::function<void (const canvas::Point &)> OnPositionChanged;
	void onPositionChanged( const OnPositionChanged &callback );	

protected:
	//	Properties
	void applyBounds(PropertyImpl<canvas::Rect> *prop);
	void applyZIndex();

	canvas::Canvas *canvas();
	bool createSurface( const canvas::Rect &rect );

	virtual void calculateBounds( canvas::Rect &size );
	const canvas::Rect &bounds() const;
	
	virtual void getZIndex( int &zIndex );

private:
	canvas::Canvas *_canvas;
	canvas::Surface *_surface;
	canvas::Rect _bounds;
	int _zIndex;
	OnSizeChanged _onSizeChanged;
	OnPositionChanged _onPositionChanged;	
};

}
