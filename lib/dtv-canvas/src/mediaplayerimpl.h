#pragma once

#include "mediaplayer.h"

namespace canvas {

class System;
class Window;
class VideoOverlay;

class MediaPlayerImpl : public MediaPlayer {
public:
	MediaPlayerImpl( System *sys );
	virtual ~MediaPlayerImpl();

	virtual bool initialize( const Rect &rect, const std::string &url );
	virtual void finalize();

	//	Position/size
	virtual void move( const Point &point );
	virtual void resize( const Size &size );

protected:
	bool getVideoDescription( VideoDescription &desc );
	void size( Size &size );
	System *system() const;
	
private:
	System *_sys;
	VideoOverlay *_video;
};

}

