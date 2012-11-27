#include "soundplayer.h"
#include "soundproperties.h"
#include "../device.h"
#include <canvas/mediaplayer.h>
#include <util/mcr.h>

namespace player {

SoundPlayer::SoundPlayer( Device *dev )
	: Player( dev )
{
	_media = dev->createMediaPlayer();
	_sound = new SoundProperties( _media );

	_media->onStop( boost::bind(&SoundPlayer::stop,this) );	
}

SoundPlayer::~SoundPlayer()
{
	delete _sound;
}

bool SoundPlayer::startPlay() {
	if (_media->initialize( url() )) {
		_media->play();
		return true;
	}
	return false;
}

void SoundPlayer::stopPlay() {
	_media->stop();
}

void SoundPlayer::pausePlay( bool needPause ) {
	_media->pause( needPause );
}

bool SoundPlayer::supportSchemma( schema::type sch ) const {
	return sch == schema::file || sch == schema::rtp || sch == schema::rtsp;
}

void SoundPlayer::registerProperties() {
	Player::registerProperties();
	_sound->registerProperties(this);
}

}
