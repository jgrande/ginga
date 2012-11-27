#include <util/registrator.h>
#include <gtest/gtest.h>

#ifdef _WIN32
#	ifdef _DEBUG
#		pragma comment(lib,"gtestd.lib")
#	else
#		pragma comment(lib,"gtest.lib")
#	endif // _DEBUG
#endif

int main( int argc, char **argv ) {
	int result;
	util::reg::init();
	testing::InitGoogleTest( &argc, argv );
	result = RUN_ALL_TESTS();
	util::reg::fin();
	return result;
}

