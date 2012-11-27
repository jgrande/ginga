#include "configregistrator.h"
#include <boost/foreach.hpp>
#include <string>

namespace util {
namespace cfg {

ConfigRegistrator::ConfigRegistrator( const std::string &name, reg::impl::addCallback aCall )
	: Registrator( name, aCall )
{
}

ConfigRegistrator::~ConfigRegistrator() {
}

PropertyTree &ConfigRegistrator::root() {
	const std::string &val = name();
	if (val.find(".") != std::string::npos) {
		return get() (val.substr(0,val.rfind(".")));
	} else {
		return get();
	}
}

}
}
