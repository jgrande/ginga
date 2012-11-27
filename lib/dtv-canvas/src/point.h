#pragma once

namespace canvas {

class Rect;

class Point {
public:
	Point();
	Point( int x, int y );
	explicit Point( const Rect &rect );
	~Point( void );
	
	bool operator==(const Point& point) const;
	bool operator!=(const Point& point) const;

	int x;
	int y;
};
	
}
