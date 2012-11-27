#include "videoplayer.h"
#include "soundproperties.h"
#include "../device.h"
#include <canvas/mediaplayer.h>
#include <canvas/player.h>
#include <canvas/window.h>
#include <canvas/surface.h>
#include <canvas/system.h>
#include <util/mcr.h>

namespace player {

VideoPlayer::VideoPlayer( Device *dev )
	: GraphicPlayer( dev )
{
	_media = dev->createMediaPlayer();
	_sound = new SoundProperties( _media );

	_media->onStop( boost::bind(&VideoPlayer::stop,this) );
}

VideoPlayer::~VideoPlayer()
{
	delete _sound;
	delete _media;
}

bool VideoPlayer::startPlay() {
	if (GraphicPlayer::startPlay()) {
		//	Set surface transparent
		surface()->flushCompositionMode( canvas::composition::source );
		
		//	Initialize media player
		if (!_media->initialize( surface()->getBounds(), url() )) {
			return false;
		}

		//	Play
		_media->play();
		
		return true;
	}
	return false;
}

void VideoPlayer::stopPlay() {
	_media->stop();
	_media->finalize();
	GraphicPlayer::stopPlay();
}

void VideoPlayer::registerProperties() {
	GraphicPlayer::registerProperties();
	_sound->registerProperties(this);
}

void VideoPlayer::pausePlay( bool pause ) {
	_media->pause( pause );
}

//	Events
void VideoPlayer::onSizeChanged( const canvas::Size &size ) {
	//	Resize
	_media->resize( size );
}

void VideoPlayer::onPositionChanged( const canvas::Point &point ) {
	//	Move video widget
	_media->move( point );
}

bool VideoPlayer::supportSchemma( schema::type sch ) const {
	return sch == schema::file || sch == schema::rtp || sch == schema::rtsp || sch == schema::sbtvd;
}

}
