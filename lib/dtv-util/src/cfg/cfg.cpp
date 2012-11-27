#include "cfg.h"

namespace util {
namespace cfg {

static PropertyTree _cfg;

PropertyTree &get() {
	return _cfg;
}

PropertyTree &get( const std::string &path ) {
	return _cfg(path);
}

}
}
