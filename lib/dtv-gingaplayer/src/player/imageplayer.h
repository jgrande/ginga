#pragma once

#include "graphicplayer.h"

namespace player {

class ImagePlayer : public GraphicPlayer {
public:
	ImagePlayer( Device *dev );
	virtual ~ImagePlayer();

protected:
	virtual void refresh();
};

}
