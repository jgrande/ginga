#pragma once

#include <vector>

namespace canvas {

class Size;
class Point;

class Rect {
public:
	Rect();
	Rect( int x, int y, int w, int h );
	Rect( const Point &point, const Size &size );
	~Rect();

	bool operator==(const Rect& rect) const;
	bool operator!=(const Rect& rect) const;

	Rect &operator=( const Rect &rect );
	Rect &operator=( const Point &point );
	Rect &operator=( const Size &size );
	
	bool includes( const Rect &rect ) const;
	bool intersects( const Rect& rect ) const;
	bool intersection( const Rect &rect, Rect &intersection ) const;
	bool abuts( const Rect& rect, float percentage = 0.0 ) const;
	Rect encompass( const Rect& rect ) const;
	bool isEmpty() const;
	int area() const;
	Rect cut( const Rect& rect ) const;
	std::vector<Rect> divide( const Rect& rect ) const;

	bool aside( const Rect& rect ) const;
	bool goesInto( const Rect& rect ) const;
	bool goesThrough( const Rect& rect ) const;

	int x;
	int y;
	int w;
	int h;
};
	
}
