#include "../../src/presentationenginemanager.h"
#include <gingaplayer/system.h>
#include <canvas/canvas.h>
#include <canvas/system.h>
#include <gingaplayer/device.h>
#include <util/mcr.h>
#include <gtest/gtest.h>

namespace bptgn = br::pucrio::telemidia::ginga::ncl;

TEST( Presenter, pem ) {
	player::System *sys = new player::System();
	player::Device *dev = new player::Device( sys );
	dev->initialize();
	sys->addDevice( dev );

	bptgn::PresentationEngineManager* pem = new bptgn::PresentationEngineManager( sys );
	ASSERT_TRUE( pem != NULL );

	DEL( pem );
	DEL( sys );
}
