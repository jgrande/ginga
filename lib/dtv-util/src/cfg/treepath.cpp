#include "treepath.h"

#include <string>

namespace util {
namespace cfg {

TreePath::TreePath( const std::string &str )
	: _path(str) {
}

TreePath::~TreePath() {
}

const std::string TreePath::property() const {
	return _path.substr(_path.rfind( "." ) + 1, _path.length());
}
const std::string TreePath::root() const {
	return _path.substr(0, _path.find( "." ));
}
const std::string TreePath::withoutRoot() const {
	return _path.substr(_path.find( "." ) + 1, _path.length());
}
const std::string TreePath::path() const {
	return _path.substr(0, _path.rfind( "." ));
}
const std::string &TreePath::string() const {
	return _path;
}
bool TreePath::walkable() const {
	return ( _path.find(".") != std::string::npos );
}

}
}
