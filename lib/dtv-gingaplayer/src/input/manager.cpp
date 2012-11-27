#include "manager.h"
#include <util/log.h>
#include <util/mcr.h>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

namespace player {
namespace input {

class Listener {
public:
	Listener( const ListenerId &id, const InputCallback &callback, const ::util::key::Keys &keys)
		: _id( id ), _callback( callback ), _keys( keys ), _enabled( true )
	{}
	virtual ~Listener( void ) {}

	const ListenerId &id() const { 
		return _id;
	}
	
	bool hasReserved( ::util::key::type key ) const {
		return ( _enabled &&
			_keys.size() != 0 && 
			std::find( _keys.begin(), _keys.end(), key ) != _keys.end());
	}

	void dispatchKey( ::util::key::type key, bool isUp ) {
		_callback( key, isUp );
	}
	
	void reserveKeys( const ::util::key::Keys &keys ) {
		BOOST_FOREACH( ::util::key::type key, keys ) {_keys.insert(key);}
	}
	
	const ::util::key::Keys &getKeys(){ 
		return _keys; 
	}
	
	bool isEnabled() const { return _enabled; }
	
	void enabled( bool enabled ){ _enabled = enabled; }

private:
	ListenerId _id;
	InputCallback _callback;
	::util::key::Keys _keys;
	bool _enabled;
};

struct ListenerFinder {
	const ListenerId &_id;
	ListenerFinder( const ListenerId &id ) : _id( id ) {}
	bool operator()( input::Listener *listener ) const {
		return listener->id() == _id;
	}
};

Manager::Manager( void )
{
}

Manager::~Manager( void )
{
	CLEAN_ALL(input::Listener *,_listeners);
}

bool Manager::addInputListener( const ListenerId &id, const InputCallback &callback, const ::util::key::Keys &keys ) {
	input::Listener *listener;
	ListenerFinder finder(id);

	LDEBUG("Manager", "Reserve keys: listeners=%d, id=%p, size=%d", _listeners.size(), id, keys.size());

	input::Listeners::iterator it=std::find_if( _listeners.begin(), _listeners.end(), finder );
	if (it == _listeners.end()) {
		listener = new input::Listener( id, callback, keys );
		_listeners.push_back( listener );
	}
	else {
		//  Listener found, add keys
		listener = (*it);
		listener->enabled( true );
		listener->reserveKeys( keys );
	}
	updateGlobalKeys(true, keys);
	return true;
}

bool Manager::delInputListener( const ListenerId &id ) {
	input::Listener *listener;
	ListenerFinder finder(id);

	input::Listeners::iterator it=std::find_if( _listeners.begin(), _listeners.end(), finder );
	if (it != _listeners.end()) {
		listener = (*it);
		if(listener->isEnabled()) {
			listener->enabled( false );
			updateGlobalKeys(false, listener->getKeys());
			LDEBUG("Manager", "listener removed, id=%p", id);
			return true;
		}
	}
	return false;
}

bool Manager::dispatchKey( ::util::key::type key, bool isUp ) {
	LDEBUG("Manager", "Dispatch key code: listeners=%d, key=%d", _listeners.size(), key);
	input::Listeners tmp = _listeners;
	BOOST_FOREACH( input::Listener *listener, tmp ) {
		if (listener->hasReserved( key )) {
			listener->dispatchKey( key, isUp );
			LDEBUG("Manager", "Dispatch key, key=%d, listener=%p", key, listener->id() );
		}
	}
	
	//	clean up disabled listeners
	{
		input::Listener *listener;
		input::Listeners::iterator it = _listeners.begin();
		while (it != _listeners.end()) {
			listener = (*it);
			if ( !listener->isEnabled() ){
				it = _listeners.erase( it );
				delete listener;
			}else{
				it++;
			}
		}
	}
	return true;
}

void Manager::onGlobalKeysChange( const ReservedKeysCallback &callback ){
	_onGlobalKeysChange = callback;
}

void Manager::updateGlobalKeys(bool isAdd, const ::util::key::Keys &keys)
{
	bool modified = false;
	if (!keys.size())
		return;

	::util::key::Keys::iterator k = keys.begin();
	::util::key::Keys::iterator gk;

	while (k != keys.end()) {
		util::key::type key = (util::key::type)*k;
		gk = _globalKeys.find(key);

		if (isAdd) {
			_globalKeys.insert(key);
			modified |= (gk == _globalKeys.end());
		} else {
			if (gk != _globalKeys.end()) {
				_globalKeys.erase(gk);
				modified |= _globalKeys.find(key) == _globalKeys.end();
			}
		}
		++k;
	}

	if(modified && !_onGlobalKeysChange.empty()){
		_onGlobalKeysChange( _globalKeys );
	}
}

}
}
