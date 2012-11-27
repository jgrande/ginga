#include "videooverlay.h"
#include "rect.h"
#include "point.h"
#include <util/log.h>

namespace canvas {

VideoOverlay::VideoOverlay()
{
}

VideoOverlay::~VideoOverlay()
{
}

//	Initialization
bool VideoOverlay::initialize( const Rect &rect ) {
	LDEBUG( "VideoOverlay", "Initialize: rect=(%d,%d,%d,%d)", rect.x, rect.y, rect.w, rect.h );
	return true;
}

void VideoOverlay::finalize() {
	LDEBUG( "VideoOverlay", "Finalize" );
}

bool VideoOverlay::move( const Point &point ) {
	LDEBUG( "VideoOverlay", "Move: point=(%d,%d)", point.x, point.y );
	return true;
}

bool VideoOverlay::resize( const Size &size ) {
	LDEBUG( "VideoOverlay", "Resize: size=(%d,%d)", size.w, size.h );
	return true;
}

void VideoOverlay::size( Size &size ) {
	size.w = 0;
	size.h = 0;
}

bool VideoOverlay::getDescription( VideoDescription &desc ) {
#ifdef _WIN32
	desc = NULL;
#else
	desc.display = NULL;
	desc.screenID = -1;
	desc.winID = -1;
#endif
	return true;
}

}
