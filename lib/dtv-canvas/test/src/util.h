#pragma once

#include <string>

namespace canvas {
	class Canvas;
	class System;
}

namespace util  {

std::string getImageName( const std::string &name );
bool compareImages( canvas::Canvas *c, const std::string &file );

}

