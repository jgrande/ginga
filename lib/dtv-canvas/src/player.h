#pragma once

namespace canvas {

class System;
class MediaPlayer;

class Player {
public:
	Player();
	virtual ~Player();

	//	Initialization
	virtual bool initialize();
	virtual void finalize();

	virtual MediaPlayer *create( System *win ) const=0;

	static Player *createPlayer();
};

}

