#pragma once

#include <canvas/size.h>
#include <canvas/point.h>
#include <canvas/rect.h>

namespace canvas {
	class Canvas;
}

namespace player {
namespace check {

template<typename T>
	inline bool always( const T & ) {
	return true;
}

template<typename T>
	inline bool never( const T & ) {
	return false;
}

template<typename T>
	inline bool range( const T &value, const T &min, const T &max ) {
	return value >= min && value <= max;
}

bool color( const std::string &color );
bool position( canvas::Canvas *canvas, const canvas::Point &point );
bool size( canvas::Canvas *canvas, const canvas::Size &size );
bool bounds( canvas::Canvas *canvas, const canvas::Rect &bounds );
bool fileExists( const std::string &file );
inline bool notEmpty( const std::string &str ) {
	return str.empty() ? false : true;
}

}
}

