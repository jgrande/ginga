#include "player.h"
#include <util/registrator.h>
#include <util/cfg/cfg.h>
#include <util/log.h>
#include <gtest/gtest.h>
#include <boost/thread.hpp>

#ifdef _WIN32
#	ifdef _DEBUG
#		pragma comment(lib,"gtestd.lib")
#	else
#		pragma comment(lib,"gtest.lib")
#	endif // _DEBUG
#endif


void runAllTests( int *result ) {
	*result = RUN_ALL_TESTS();
	stop();
}

int main( int argc, char **argv ) {
	int result;
	util::reg::init();
	util::log::init();
	// util::log::setLevel( "gingaplayer", "all", "debug" );
	// util::cfg::setValue( "gui.canvas.use", "gtk" );
	init();

	testing::InitGoogleTest( &argc, argv );
	boost::thread thread = boost::thread( boost::bind( &runAllTests, &result ) );

	run();
	thread.join();
	fin();

	util::log::fin();
	util::reg::fin();
	return result;
}
