#include "surface.h"
#include "../../../src/canvas.h"
#include "../../../src/system.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

void Surface::SetUp( void ) {
	System::SetUp();
	getCanvas()->reset();
}

void Surface::TearDown( void ) {
	System::TearDown();
}

canvas::Canvas* Surface::getCanvas() {
	return System::getSystem()->canvas();
}

std::string Surface::getExpectedPath( const std::string &fileName ) const {
    fs::path root;
    root /= "Surface";
    root /= getSubDirectory();
    root /= fileName;
    return root.string();
}

std::string Surface::getSubDirectory() const {
    return "Basic";
}
