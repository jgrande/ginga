#include "font.h"
#include <boost/algorithm/string.hpp>
#include <vector>
#include <algorithm>

namespace canvas {

Font::Font()
{
	_families.push_back(DEFAULT_FONT);
	_size = 10;
	_bold = false;
	_italic = false;
	_smallCaps = false;
}

Font::Font( const std::vector<std::string> &families, size_t size, bool bold, bool italic, bool smallCaps )
	: _families( families )
{
	_size = size;
	_bold = bold;
	_italic = italic;
	_smallCaps = smallCaps;

	//	Add default font
	addDefault();	
}

Font::Font( const char *faces, size_t size, bool bold, bool italic, bool smallCaps )
{
	_size = size;
	_bold = bold;
	_italic = italic;
	_smallCaps = smallCaps;

	//	Add families
	boost::split( _families, faces, boost::is_any_of( "," ) );
	addDefault();
}

Font::~Font()
{
}

//	SETTERS
void Font::families( const std::vector<std::string> &families ) {
	_families = families;
	addDefault();
}

void Font::size( size_t size ) {
	_size = size;
}

void Font::bold( bool enable ) {
	_bold = enable;
}

void Font::italic( bool enable ) {
	_italic = enable;
}

void Font::smallCaps( bool enable ) {
	_smallCaps = enable;
}

//	GETTERS
const std::vector<std::string>& Font::families() const {
	return _families;
}

std::string Font::familiesAsString() const {
	std::string tmp;
	for (size_t i=0; i<_families.size(); i++) {
		if (i) {
			tmp += ",";
		}
		tmp += _families[i];
	}
	return tmp;
}

size_t Font::size() const {
	return _size;
}

bool Font::bold() const {
	return _bold;
}

bool Font::italic() const {
	return _italic;
}

bool Font::smallCaps() const {
	return _smallCaps;
}

void Font::addDefault() {
	std::vector<std::string>::iterator it = std::find( _families.begin(), _families.end(), DEFAULT_FONT );
	if (it == _families.end()) {
		_families.push_back(DEFAULT_FONT);
	}
}

}
