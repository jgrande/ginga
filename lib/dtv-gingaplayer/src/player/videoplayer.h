#pragma once

#include "graphicplayer.h"

namespace canvas {
	class MediaPlayer;
}

namespace player {

class SoundProperties;

class VideoPlayer : public GraphicPlayer {
public:
	VideoPlayer( Device *dev );
	virtual ~VideoPlayer();

protected:
	virtual bool startPlay();
	virtual void stopPlay();
	virtual void registerProperties();
	virtual void pausePlay( bool pause );
	virtual bool supportSchemma( schema::type sch ) const;

	//	Events
	virtual void onSizeChanged( const canvas::Size &size );
	virtual void onPositionChanged( const canvas::Point &point );	
	
private:
	canvas::MediaPlayer *_media;
	SoundProperties *_sound;
};

}
