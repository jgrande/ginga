#include "mediaplayer.h"
#include "player.h"
#include "../../point.h"
#include "../../system.h"
#include <util/log.h>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <vlc/vlc.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

namespace canvas {
namespace vlc {

static void vlcCallback(const libvlc_event_t *p_event, void *p_user_data) {
	if (p_event->type == libvlc_MediaPlayerEndReached) {
		assert(p_user_data);
		MediaPlayer *mp = (MediaPlayer *)p_user_data;
		mp->onStopped();
	}
}

MediaPlayer::MediaPlayer( System *sys, Player *player )
	: canvas::MediaPlayerImpl( sys )
{
	_player = player;
	_mp = NULL;
}

MediaPlayer::~MediaPlayer()
{
	if (_mp) {
		libvlc_media_player_release( _mp );
	}
}

//	Initialization
bool MediaPlayer::initialize( const std::string &url ) {
	LDEBUG( "vlc", "Initialize: url=%s", url.c_str() );
	
	//	Create media from url
	libvlc_media_t *m=libvlc_media_new_path( instance(), url.c_str() );
	if (!m) {
		LERROR( "vlc", "Cannot initialize new media from url: url=%s", url.c_str() );
		return false;
	}

	//	Add common parameters
	libvlc_media_add_option( m, "verbose=1000" );
	libvlc_media_add_option( m, "no-osd" );
	libvlc_media_add_option( m, "ffmpeg-hw" );

	//	Create a media player playing environement
	_mp = libvlc_media_player_new_from_media(m);
	if (!_mp) {
		libvlc_media_release (m);
		LERROR( "vlc", "Cannot create media player from url: url=%s", url.c_str() );
		return false;
	}

	//	No need to keep the media now
	libvlc_media_release (m);

	{	//	Set WindowID
		VideoDescription desc;
		if (getVideoDescription( desc )) {
#ifndef _WIN32
			libvlc_media_player_set_xwindow( _mp, desc.winID );
#else
			libvlc_media_player_set_hwnd( _mp, desc );
#endif
		}
	}

	{	//	Attach to stop asyn events
		libvlc_event_manager_t *mgr=libvlc_media_player_event_manager( _mp );
		libvlc_event_attach( mgr, libvlc_MediaPlayerEndReached, vlcCallback, this ); 
	}

	return true;
}

void MediaPlayer::finalize() {
	LDEBUG( "vlc", "Finalize" );
	assert(_mp);

	{	//	Dettach to stop asyn events
		libvlc_event_manager_t *mgr=libvlc_media_player_event_manager( _mp );
		libvlc_event_detach( mgr, libvlc_MediaPlayerEndReached, vlcCallback, this ); 
	}

	//	Release player
	libvlc_media_player_release( _mp );
	_mp = NULL;

	MediaPlayerImpl::finalize();
}

//	Media operations
void MediaPlayer::play() {
	LDEBUG( "vlc", "Play" );
	assert(_mp);	
	//	play the media_player
	libvlc_media_player_play( _mp );
}

void MediaPlayer::stop() {
	LDEBUG( "vlc", "Stop" );
	assert(_mp);	
	//	Stop playing	
	libvlc_media_player_stop(_mp);
}

void MediaPlayer::pause( bool pause ) {
	LDEBUG( "vlc", "Pause: param=%d", pause );
	assert(_mp);	
	//	Pause playing
	libvlc_media_player_set_pause(_mp, pause ? 1 : 0 );
}

//	Volume
void MediaPlayer::mute( bool needMute ) {
	LDEBUG( "vlc", "Mute: param=%d", needMute );	
	assert(_mp);	
	libvlc_audio_set_mute( _mp, needMute ? 1 : 0 );
}

void MediaPlayer::volume( Volume vol ) {
	LDEBUG( "vlc", "Volume: param=%d", vol );		
	assert(_mp);	
	libvlc_audio_set_volume( _mp, vol );
}

//	Aux
libvlc_instance_t *MediaPlayer::instance() const {
	return _player->instance();
}

void MediaPlayer::onStopped() {
	system()->enqueue( boost::bind(&MediaPlayer::onMediaStopped,this) ); // TODO: validate pointer!
}

}
}

