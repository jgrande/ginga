#pragma once

#include "input.h"
#include <boost/interprocess/containers/stable_vector.hpp>
namespace player {
namespace input {

class Listener;
typedef boost::container::stable_vector<Listener *> Listeners;

class Manager {
public:
	Manager( void );
	virtual ~Manager( void );

	bool dispatchKey( ::util::key::type key, bool isUp );
	bool addInputListener( const ListenerId &id, const InputCallback &callback, const ::util::key::Keys &keys );
	bool delInputListener( const ListenerId &id );
	void updateGlobalKeys( bool isAdd, const ::util::key::Keys &keys );
	void onGlobalKeysChange( const ReservedKeysCallback &callback );

private:
	input::Listeners     _listeners;
	::util::key::Keys    _globalKeys;
	ReservedKeysCallback _onGlobalKeysChange ;
};

}
}
