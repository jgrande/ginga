#include "player.h"
#include "mediaplayer.h"

namespace canvas {
namespace dummy {

Player::Player()
{
}

Player::~Player()
{
}

canvas::MediaPlayer *Player::create( System * /*sys*/ ) const {
	return new MediaPlayer();
}

}
}

