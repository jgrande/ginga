#pragma once

#include "../player.h"

namespace canvas {
	class MediaPlayer;
}

namespace player {

class SoundProperties;

class SoundPlayer : public player::Player {
public:
	SoundPlayer( Device *dev );
	virtual ~SoundPlayer();

protected:
	virtual bool startPlay();
	virtual void stopPlay();
	virtual void pausePlay( bool pause );
	virtual bool supportSchemma( schema::type sch ) const;		
	virtual void registerProperties();

private:
	canvas::MediaPlayer *_media;
	SoundProperties *_sound;
};

}
