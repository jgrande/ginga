#include "mediaplayerimpl.h"
#include "videooverlay.h"
#include "window.h"
#include "system.h"
#include <util/log.h>
#include <util/mcr.h>

namespace canvas {

MediaPlayerImpl::MediaPlayerImpl( System *sys )
{
	assert(sys);
	_sys = sys;
	_video = NULL;
}

MediaPlayerImpl::~MediaPlayerImpl()
{
	assert(!_video);
}

bool MediaPlayerImpl::initialize( const Rect &rect, const std::string &url ) {
	Window *win = _sys->window();
	
	//	Create video overlay
	_video = win->createVideoOverlay();
	if (!_video) {
		return false;
	}

	//	Initialize video overlay
	if (!_video->initialize( rect )) {
		win->destoyVideoOverlay( _video );
		return false;
	}

	//	HACK gcc
	MediaPlayer *ptr = (MediaPlayer *)this;
	if (!ptr->initialize( url )) {
		MediaPlayerImpl::finalize();
		return false;
	}

	return true;
}

void MediaPlayerImpl::finalize() {
	if (_video) {
		_video->finalize();
		_sys->window()->destoyVideoOverlay( _video );		
	}
}

bool MediaPlayerImpl::getVideoDescription( VideoDescription &desc ) {
	if (_video) {
		return _video->getDescription( desc );
	}
	return false;
}

//	Position/size
void MediaPlayerImpl::move( const Point &point ) {
	if (_video) {
		_video->move( point );
	}
}

void MediaPlayerImpl::resize( const Size &size ) {
	if (_video) {
		_video->resize( size );
	}
}

void MediaPlayerImpl::size( Size &size ) {
	if (_video) {
		_video->size( size );
	}
	else {
		size.w = 0;
		size.h = 0;
	}
}

System *MediaPlayerImpl::system() const {
	return _sys;
}

}

