#pragma once

#include <string>

namespace player {
namespace settings {

class Module;

namespace prefix {
#define PREFIX_LIST(fnc) \
	fnc( system, "system" ) \
	fnc( user, "user" ) \
	fnc( defaults, "default" ) \
	fnc( service, "service" ) \
	fnc( si, "si" ) \
	fnc( channel, "channel" ) \
	fnc( shared, "shared" ) \

#define DO_ENUM_PREFIX(t, s) t,
enum type
{
	unknown = 0,
	PREFIX_LIST(DO_ENUM_PREFIX)
	LAST
};
#undef DO_ENUM_PREFIX
}

void init( void );
void fin( void );

void addListener( Module *module );
void delListener( Module *module );

void setProperty( const std::string &name, const std::string &value, bool init=false );
const std::string getProperty( const std::string &name );

}
}
