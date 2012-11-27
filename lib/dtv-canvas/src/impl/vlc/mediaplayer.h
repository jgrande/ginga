#pragma once

#include "../../mediaplayerimpl.h"

struct libvlc_instance_t;
struct libvlc_media_player_t;
struct libvlc_media_t;

namespace canvas {
namespace vlc {

class Player;

class MediaPlayer : public canvas::MediaPlayerImpl {
public:
	MediaPlayer( System *sys, Player *player );
	virtual ~MediaPlayer();

	//	Initialization
	virtual bool initialize( const std::string &url );
	virtual void finalize();

	//	Media operations
	virtual void play();
	virtual void stop();
	virtual void pause( bool needPause );

	//	Volume
	virtual void mute( bool needMute );
	virtual void volume( Volume vol );

	//	Aux
	void onStopped();

protected:
	//	Aux
	libvlc_instance_t *instance() const;

private:
	Player *_player;	
	libvlc_media_player_t *_mp;
};

}
}

