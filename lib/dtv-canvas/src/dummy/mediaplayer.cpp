#include "mediaplayer.h"
#include "../rect.h"
#include "../point.h"
#include <util/log.h>

namespace canvas {
namespace dummy {

MediaPlayer::MediaPlayer()
{
}

MediaPlayer::~MediaPlayer( void )
{
}

//	Initialization
bool MediaPlayer::initialize( const Rect &rect, const std::string &url ) {
	LDEBUG("dummy::MediaPlayer", "Initialize: rect=(%d,%d,%d,%d), url=%s",
		rect.x, rect.y, rect.w, rect.h, url.c_str());	
	return true;
}

bool MediaPlayer::initialize( const std::string &url ) {
	LDEBUG("dummy::MediaPlayer", "Initialize: url=%s", url.c_str());	
	return true;
}

void MediaPlayer::finalize() {
	LDEBUG("dummy::MediaPlayer", "Finalize");
}

//	Stream operations
void MediaPlayer::play() {
	LDEBUG("dummy::MediaPlayer", "Play");
}

void MediaPlayer::stop() {
 	LDEBUG("dummy::MediaPlayer", "Stop");
}

void MediaPlayer::pause( bool needPause ) {
 	LDEBUG("dummy::MediaPlayer", "Pause: value=%d", needPause);
}

//	Volume
void MediaPlayer::mute( bool needMute ) {
 	LDEBUG("dummy::MediaPlayer", "mute: value=%d", needMute);
}

void MediaPlayer::volume( Volume vol ) {
 	LDEBUG("dummy::MediaPlayer", "volume: value=%d", vol);
}

//	Position/size
void MediaPlayer::move( const Point &point ) {
	LDEBUG("dummy::MediaPlayer", "move(%d,%d)", point.x, point.y);
}

void MediaPlayer::resize( const Size &size ) {
	LDEBUG("dummy::MediaPlayer", "resize(%d,%d)", size.w, size.h);
}

}
}
