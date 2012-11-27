#include "registrator.h"
#include <boost/algorithm/string/replace.hpp>
#include <boost/foreach.hpp>

namespace util {
namespace reg {
namespace impl {

static inline bool compareByPriority( const Registrator *first, const Registrator *second) {
	return ( first->priority() < second->priority());
}

static std::list<Registrator *> &initCallbacks() {
	static std::list<Registrator *> initCallbacks;
	return initCallbacks;
}

static std::list<Registrator *> &finCallbacks() {
	static std::list<Registrator *> finCallbacks;
	return finCallbacks;
}

static inline void call( std::list<Registrator *> &calls ) {
	if (!calls.empty()) {
		calls.sort(impl::compareByPriority);
		BOOST_FOREACH( Registrator *reg, calls ) {
			( *reg )( );
		}
		calls.clear();
	}
}

}       //	namespace impl


void addinitCallbacks(Registrator *aReg) {
	impl::initCallbacks().push_front( aReg );
}

void addfinCallbacks(Registrator *aReg) {
	impl::finCallbacks().push_front( aReg );

}

void init() {
	impl::call( impl::initCallbacks() );
}

void fin() {
	impl::call( impl::finCallbacks() );
}

Registrator::Registrator(  const std::string &name, impl::addCallback aCall )
	: _name( name ) {
	boost::replace_all(_name,"_",".");
	( *aCall )( this );
}

Registrator::~Registrator() {
}

const std::string &Registrator::name() const {
	return _name;
}

void Registrator::operator()() {
}

int Registrator::priority() const {
	return count(_name.begin(), _name.end(), '.');
}

}       // end reg namespace
}       // end util namespace
