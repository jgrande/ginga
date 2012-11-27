#pragma once

#include "../mediaplayer.h"

namespace canvas {
namespace dummy {

class MediaPlayer : public canvas::MediaPlayer {
public:
	MediaPlayer();
	virtual ~MediaPlayer();

	//	Initialization
	virtual bool initialize( const Rect &rect, const std::string &url );
	virtual bool initialize( const std::string &url );
	virtual void finalize();

	//	Stream operations
	virtual void play();
	virtual void stop();
	virtual void pause( bool needPause );

	//	Volume
	virtual void mute( bool needMute );
	virtual void volume( Volume vol );

	//	Position/size
	virtual void move( const Point &point );
	virtual void resize( const Size &size );
};

}
}

