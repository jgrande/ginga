#pragma once

#include "../../player.h"

struct libvlc_instance_t;

namespace canvas {
namespace vlc {

class Player : public canvas::Player {
public:
	Player();
	virtual ~Player();

	//	Initialization
	virtual bool initialize();
	virtual void finalize();

	//	Instance creation
	virtual canvas::MediaPlayer *create( System *sys ) const;

	//	Aux implementation
	libvlc_instance_t *instance() const;
	
private:
	libvlc_instance_t *_vlc;
};

}
}

