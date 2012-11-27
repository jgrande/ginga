#include "mediaplayer.h"

namespace canvas {

MediaPlayer::MediaPlayer()
{
}

MediaPlayer::~MediaPlayer()
{
}

void MediaPlayer::onStop( const OnStopCallback &callback ) {
	_onStop = callback;
}

void MediaPlayer::onMediaStopped() {
	if (!_onStop.empty()) {
		_onStop();
	}
}

}

