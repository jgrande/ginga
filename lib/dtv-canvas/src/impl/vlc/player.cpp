#include "player.h"
#include "mediaplayer.h"
#include <util/log.h>
#include <vlc/vlc.h>
#include <string.h>
#include <stdio.h>

namespace canvas {
namespace vlc {

Player::Player()
{
	_vlc = NULL;
}

Player::~Player()
{
	assert(!_vlc);
}

libvlc_instance_t *Player::instance() const {
	return _vlc;
}

//	Initialization
bool Player::initialize() {
	LINFO( "vlc", "Initialize" );
	const char *args[] = {
		"-I",	//	Dummy
		"--no-osd",
		"--no-video-title-show",
		"--ignore-config",
		//		"--extraintf=logger", // Log anything
		//		"--verbose=2", // Be much more verbose then normal for debugging purpose		
		"--no-xlib",
		NULL
	};
	int argc = sizeof(args)/sizeof(args[0]);
	argc--;
	_vlc = libvlc_new( argc, args );
	return _vlc ? true : false;
}

void Player::finalize() {
	LINFO( "vlc", "Finalize" );
	libvlc_release (_vlc);
	_vlc = NULL;
}

//	Media player
canvas::MediaPlayer *Player::create( System *sys ) const {
	return new MediaPlayer( sys, (Player *)this );
}

}
}

