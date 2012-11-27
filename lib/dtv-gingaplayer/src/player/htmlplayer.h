#pragma once

#include "graphicplayer.h"

namespace canvas {
	class WebViewer;
}

namespace player {

class HtmlPlayer : public GraphicPlayer {
public:
	HtmlPlayer( Device *dev );
	virtual ~HtmlPlayer();

protected:
	virtual bool startPlay();
	virtual void stopPlay();
	virtual void refresh();
	virtual bool supportRemote() const;

	//	Events
	virtual void onSizeChanged( const canvas::Size &size );
	virtual void onPositionChanged( const canvas::Point &point );	

private:
	canvas::WebViewer *_html;
};

}
