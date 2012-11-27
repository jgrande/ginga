#pragma once

#include "../player.h"
#include <canvas/types.h>

namespace canvas {
	class System;
	class Surface;
}

namespace player {

namespace fit {
namespace mode {

enum type  {
	fill,
	hidden,
	meet,
	meetBest,
	slice
};

}	//	namespace mode
}	//	namespace fit

namespace property {
	class FocusHandler;
}

class GraphicProperties;
class FocusProperties;

class GraphicPlayer : public player::Player {
public:
	explicit GraphicPlayer( Device *dev );
	virtual ~GraphicPlayer();

protected:
	//	Initialization
	virtual bool startPlay();
	virtual void stopPlay();
	virtual void registerProperties();
	virtual void beginRefresh();
	virtual void onPropertyChanged();

	//	Events
	virtual void onSizeChanged( const canvas::Size &size );
	virtual void onPositionChanged( const canvas::Point &point );	

	//	Getters
	canvas::Canvas *canvas() const;
	canvas::Surface* surface() const;
	virtual bool isVisible() const;
	fit::mode::type getFitMode() const;	

private:
	std::string _fitMode;
	GraphicProperties *_graphic;
	FocusProperties *_focus;
};

}
