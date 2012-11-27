#include "player.h"
#include "mediaplayer.h"
#include "dummy/player.h"
#include "generated/config.h"
#if SYS_PLAYER_USE_VLC
#	include "impl/vlc/player.h"
#endif
#if SYS_PLAYER_USE_XINE
#	include "impl/xine/player.h"
#endif
#include <util/cfg/configregistrator.h>
#include <util/log.h>

namespace canvas {

REGISTER_INIT_CONFIG( gui_player ) {
	root().addNode( "player" )
#if SYS_PLAYER_USE_VLC
		.addValue( "use", "Player to initialize", std::string("vlc") );
#elif SYS_PLAYER_USE_XINE
		.addValue( "use", "Player to initialize", std::string("xine") );
#else
		.addValue( "use", "Player to initialize", std::string("dummy") );	
#endif
};


Player *Player::createPlayer() {
	std::string use = util::cfg::getValue<std::string> ("gui.player.use");
	
#if SYS_PLAYER_USE_VLC
	if (use == "vlc") {
		return new vlc::Player();
	}
#endif

#if SYS_PLAYER_USE_XINE
	if (use == "xine") {	
		return new xine::Player();
	}
#endif	

	return new dummy::Player();
}

Player::Player()
{
}

Player::~Player()
{
}

bool Player::initialize() {
	return true;
}

void Player::finalize() {
}

}

