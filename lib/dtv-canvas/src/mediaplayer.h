#pragma once

#include "types.h"
#include <string>
#include <boost/function.hpp>

namespace canvas {

class MediaPlayer {
public:
	MediaPlayer();
	virtual ~MediaPlayer();

	typedef boost::function<void (void)> OnStopCallback;
	void onStop( const OnStopCallback &callback );

	//	Initialization
	virtual bool initialize( const Rect &rect, const std::string &url )=0;
	virtual bool initialize( const std::string &url )=0;
	virtual void finalize()=0;

	//	Media operations
	virtual void play()=0;
	virtual void stop()=0;
	virtual void pause( bool needPause )=0;

	//	Volume
	virtual void mute( bool needMute )=0;
	virtual void volume( Volume vol )=0;

	//	Position/size
	virtual void move( const Point &point )=0;
	virtual void resize( const Size &size )=0;

protected:
	void onMediaStopped();
	
private:
	OnStopCallback _onStop;	
};

}

