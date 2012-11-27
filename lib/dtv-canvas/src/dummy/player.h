#pragma once

#include "../player.h"

namespace canvas {
namespace dummy {

class Player : public canvas::Player {
public:
	Player();
	virtual ~Player();

	//	Factory
	virtual canvas::MediaPlayer *create( System *sys ) const;
};

}
}

