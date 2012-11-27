#pragma once

#include <gtest/gtest.h>
#include <string>

namespace canvas {
	class Canvas;
}

namespace util  {

std::string getDepot();
std::string getTestRoot();
std::string getImageName( const std::string &name );
std::string getExpectedPath( const std::string &name, const std::string &canvas );
bool compareImages( canvas::Canvas *c, const std::string &file );
bool compareImagesFromPath( canvas::Canvas *c, const std::string &file );

}

