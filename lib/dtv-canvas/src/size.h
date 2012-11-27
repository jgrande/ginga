#pragma once

namespace canvas {

class Rect;

class Size {
public:
	Size();
	Size( int w, int h );
	explicit Size( const Rect &rect );
	~Size( void );

	bool operator==(const Size& size) const;
	bool operator!=(const Size& size) const;

	int w;
	int h;
};
	
}

