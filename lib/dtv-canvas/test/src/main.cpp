#include "system.h"
#include "../../src/system.h"
#include "generated/config.h"
#include <util/registrator.h>
#include <util/mcr.h>
#include <util/log.h>
#include <util/log/api.h>
#include <gtest/gtest.h>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#ifdef _WIN32
#	ifdef _DEBUG
#		pragma comment(lib,"gtestd.lib")
#	else
#		pragma comment(lib,"gtest.lib")
#	endif // _DEBUG
#endif

void getSystems( std::vector<std::string> &systems ) {
	UNUSED(systems);

#if SYS_SYSTEM_USE_GTK
	systems.push_back("gtk");
#endif // GTK

#if SYS_SYSTEM_USE_X11
	systems.push_back("x11");
#endif // X11

#if SYS_SYSTEM_USE_CUSTOM
	systems.push_back("custom");
#endif // CUSTOM

#if SYS_SYSTEM_USE_SDL
	systems.push_back("sdl");
#endif // SDL

#if SYS_SYSTEM_USE_QT
	systems.push_back("qt");
#endif // QT

#if SYS_SYSTEM_USE_DIRECTFB
	systems.push_back("directfb");
#endif // DIRECTFB

}

void runAllTests( int *result ) {
	*result = RUN_ALL_TESTS();
	System::getSystem()->exit();
}

int main( int argc, char **argv ) {
	int result = 0;
	int partialResult = 0;
	std::vector<std::string> systems;
	std::string error = "Using systems: ";
	getSystems( systems );

	util::reg::init();
	util::log::init();
	// util::log::setLevel( "canvas", "all", "debug" );

	testing::InitGoogleTest( &argc, argv );

	BOOST_FOREACH( std::string name, systems ) {
		impl::init( name );

		System::getSystem()->enqueue(boost::bind( &runAllTests, &partialResult ));
		System::getSystem()->run();

		util::log::flush();
		impl::fin();

		if (partialResult!=0) {
			error += name;
			error += " ";
			result += partialResult;
			partialResult = 0;
		}
	}

	
	util::log::fin();
	util::reg::fin();

	if (result!=0) {
		printf("[canvastest] Some tests failed!!! ( %s)\n", error.c_str());
	} else {
		printf("[canvastest] All tests passed!!!\n");
	}

	return result;
}
