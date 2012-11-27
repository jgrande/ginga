#include "imageplayer.h"
#include <util/log.h>
#include <canvas/rect.h>
#include <canvas/point.h>
#include <canvas/surface.h>
#include <canvas/canvas.h>
#include <canvas/system.h>
#include <boost/bind.hpp>
#include <boost/math/special_functions/round.hpp>

namespace player {

ImagePlayer::ImagePlayer( Device *dev )
	: GraphicPlayer( dev )
{
}

ImagePlayer::~ImagePlayer()
{
}

void ImagePlayer::refresh() {
	LDEBUG("ImagePlayer", "Draw image");
	canvas::Surface *image = surface()->canvas()->createSurfaceFromPath( body() );
	if (!image) {
		LWARN("ImagePlayer", "cannot create image from file=%s", body().c_str());
		return;
	}

	fit::mode::type mode = getFitMode();
	canvas::Size s_size = surface()->getSize();
	canvas::Size i_size = image->getSize();
	canvas::Rect t;	//target
	canvas::Rect s;	//source
	
	switch (mode) {
		case player::fit::mode::fill: {
			t = canvas::Rect(0, 0, s_size.w, s_size.h);
			s = canvas::Rect(0, 0, i_size.w, i_size.h);
			break;
		}
		case player::fit::mode::meet: {
			double fw = double(s_size.w)/double(i_size.w);
			double fh = double(s_size.h)/double(i_size.h);
			double factor = std::min( fw, fh );
			t = canvas::Rect(0, 0, boost::math::iround(i_size.w*factor), boost::math::iround(i_size.h*factor));
			s = canvas::Rect(0, 0, i_size.w, i_size.h);
			break;
		}
		case player::fit::mode::meetBest: {
			double fw = double(s_size.w)/double(i_size.w);
			double fh = double(s_size.h)/double(i_size.h);
			double factor = std::min( fw, fh );
			if ( factor > 2.0 ) {
				factor = 2.0;
			}
			t = canvas::Rect(0, 0, boost::math::iround(i_size.w*factor), boost::math::iround(i_size.h*factor));
			s = canvas::Rect(0, 0, i_size.w, i_size.h);
			break;
		}
		case player::fit::mode::slice: {
			double fw = double(s_size.w)/double(i_size.w);
			double fh = double(s_size.h)/double(i_size.h);
			double factor = std::max( fw, fh );
			t = canvas::Rect(
				0,
				0,
				std::min(boost::math::iround(i_size.w*factor),s_size.w),
				std::min(boost::math::iround(i_size.h*factor),s_size.h));
			s = canvas::Rect(0, 0, boost::math::iround(t.w/factor), boost::math::iround(t.h/factor));
			break;
		}
		case player::fit::mode::hidden:
		default: {
			t = s = canvas::Rect(0, 0, std::min(s_size.w, i_size.w), std::min(s_size.h, i_size.h));
			break;
		}
	};

	if (!surface()->scale( t, image, s )) {
		LWARN("ImagePlayer", "cannot draw image: image=%s, mode=%02x", body().c_str(), getFitMode());
	}

	canvas()->destroy( image );
}

}

