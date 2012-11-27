#pragma once

#include "types.h"
#include <string>

namespace canvas {

class VideoOverlay {
public:
	VideoOverlay();
	virtual ~VideoOverlay();

	//	Initialization
	virtual bool initialize( const Rect &rect );
	virtual void finalize();

	virtual bool move( const Point &point );
	virtual bool resize( const Size &size );
	virtual void size( Size &size );
	
	virtual bool getDescription( VideoDescription &desc );
};

}

