#pragma once

#include "../registrator.h"
#include "cfg.h"
#include <list>

namespace util {
namespace cfg {

class ConfigRegistrator : public reg::Registrator {
public:
	ConfigRegistrator( const std::string &name, reg::impl::addCallback aCall );
	virtual ~ConfigRegistrator();
	
protected:
	virtual PropertyTree &root();
};

#define BUILD_CONFIG_REGISTER( type, name ) \
class BUILD_CLASSNAME( type, name, ConfigRegistrator ) : public util::cfg::ConfigRegistrator { \
public: \
	BUILD_CLASSNAME( type, name, ConfigRegistrator )() : ConfigRegistrator( #name, util::reg::add##type##Callbacks ) {} \
	virtual void operator()(); \
}; \
static BUILD_CLASSNAME( type, name, ConfigRegistrator ) BUILD_INSTANCE( type, name, ConfigRegistrator ); \
void BUILD_CLASSNAME( type, name, ConfigRegistrator )::operator()()


#define REGISTER_INIT_CONFIG( name ) BUILD_CONFIG_REGISTER( init, name )
#define REGISTER_FIN_CONFIG( name ) BUILD_CONFIG_REGISTER( fin, name )

}
}

