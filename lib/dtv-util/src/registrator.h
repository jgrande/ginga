#pragma once

#include <list>
#include <string>

namespace util {
namespace reg {

class Registrator;

namespace impl{
	typedef void (*addCallback)( Registrator *);
}

void init();
void fin();
void addfinCallbacks(Registrator * aReg);
void addinitCallbacks(Registrator * aReg);

class Registrator {
public:
	Registrator( const std::string &name, impl::addCallback aCall );
	virtual ~Registrator();

	virtual void operator()();
	virtual int priority() const;
	const std::string &name() const;

private:
	std::string _name;
};

#define BUILD_BASENAME( type, name, class, target ) class##type##name##target
#define BUILD_CLASSNAME( type, name, class ) BUILD_BASENAME( type, name, class, ClassImpl )
#define BUILD_INSTANCE( type, name, class ) BUILD_BASENAME( type, name, class, Instance )

#define BUILD_REGISTER( type, name ) \
class BUILD_CLASSNAME( type, name, Registrator ) : public util::reg::Registrator { \
public: \
	BUILD_CLASSNAME( type, name, Registrator )() : util::reg::Registrator( #name, util::reg::add##type##Callbacks ) {} \
	virtual void operator()(); \
}; \
static BUILD_CLASSNAME( type, name, Registrator ) BUILD_INSTANCE( type, name, Registrator ); \
void BUILD_CLASSNAME( type, name, Registrator )::operator()()

#define REGISTER_INIT( name ) BUILD_REGISTER( init, name )
#define REGISTER_FIN( name ) BUILD_REGISTER( fin, name )

}
}
