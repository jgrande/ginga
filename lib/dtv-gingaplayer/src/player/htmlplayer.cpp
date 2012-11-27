#include "htmlplayer.h"
#include "../device.h"
#include <canvas/webviewer.h>
#include <util/mcr.h>
#include <boost/bind.hpp>

namespace player {

HtmlPlayer::HtmlPlayer( Device *dev )
	: GraphicPlayer( dev )
{
}

HtmlPlayer::~HtmlPlayer()
{
}

bool HtmlPlayer::startPlay() {
	bool result=false;
	if (GraphicPlayer::startPlay()) {
		//	Create web viewer
		_html = device()->createWebViewer( surface() );
		if (_html) {
			//	Load url
			_html->load( url() );
			result=true;
		}
	}
	return result;
}

void HtmlPlayer::stopPlay() {
	_html->stop();
	GraphicPlayer::stopPlay();
	DEL(_html);
}

//	Events
void HtmlPlayer::onSizeChanged( const canvas::Size &size ) {
	//	Redraw html
	_html->resize( size );
}

void HtmlPlayer::onPositionChanged( const canvas::Point &point ) {
	_html->move( point );
}

void HtmlPlayer::refresh() {
	_html->draw();
}

bool HtmlPlayer::supportRemote() const {
	return true;
}

}
