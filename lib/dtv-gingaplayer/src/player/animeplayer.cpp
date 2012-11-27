#include "animeplayer.h"
#include <canvas/system.h>

namespace player{

AnimePlayer::AnimePlayer( Device *dev )
	: GraphicPlayer( dev )
{
}

AnimePlayer::~AnimePlayer()
{
}

bool AnimePlayer::startPlay() {
	return true;
}

void AnimePlayer::stopPlay() {
}

}

