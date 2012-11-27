#include "util.h"
#include "../../src/canvas.h"
#include <stdio.h>
#include <boost/filesystem.hpp>

namespace util {

namespace fs = boost::filesystem;

std::string getDepot() {
	const char *root=getenv( "DEPOT" );
	return root ? root : "/";
}

std::string getTestRoot() {
	fs::path rootPath(getDepot());
	rootPath /= "lib";
	rootPath /= "dtv-canvas";
	rootPath /= "test";
	return rootPath.string();
}

std::string getImageName( const std::string &name ) {
	fs::path imagesPath( util::getTestRoot() );
	imagesPath /= "images";
	imagesPath /= name;
	return imagesPath.string();
}

std::string getExpectedPath( const std::string &name, const std::string &canvas="" ) {
	fs::path expectedPath( util::getTestRoot() );
	expectedPath /= "images";
	expectedPath /= "expected";
	if (!canvas.empty()) {
		expectedPath /= canvas;
	}
	expectedPath /= name;
	return expectedPath.string();
}

bool compareImages( canvas::Canvas *c, const std::string &file ) {
	std::string tmp = getExpectedPath( file ) + ".png";
	if (!fs::exists( tmp )) {
		tmp = getExpectedPath( file, c->name() ) + ".png";
		if (!fs::exists( tmp )) {
			printf("[util] Saving image %s\n", tmp.c_str());
			if (!c->saveAsImage( tmp ) ) {
				printf("[util] Error saving image %s\n", tmp.c_str());
			}
			return false;
		}
	}
	//	Compare
	return c->equalsImage( tmp );
}

}
