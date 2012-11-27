#pragma once

#include "graphicplayer.h"

namespace player {

class AnimePlayer : public GraphicPlayer {
public:
	AnimePlayer( Device *dev );
	virtual ~AnimePlayer();

protected:
	virtual bool startPlay();
	virtual void stopPlay();
};

}
