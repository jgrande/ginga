#pragma once

#include "types.h"
#include <util/id/pool.h>
#include <util/log.h>
#include <vector>

namespace canvas {

template<typename T>
class Event {
public:
	Event( const util::id::Ident &id, const EventCallback &callback ) : _callback(callback), _id(id) {}
	explicit Event( const EventCallback &callback ) : _callback(callback) {}
	virtual ~Event() {}

	void dispatch() { _callback( _id ); }
	const util::id::Ident &id() const { return _id; }
	T value() const { return _value; }
	void value( const T &val ) { _value = val; }
	
	void setID( const util::id::Ident &id, const T &value ) {
		_id = id;
		_value = value;
	}
	
private:
	EventCallback _callback;
	util::id::Ident _id;
	T _value;
};

template<typename Ev>
struct EventFinder {
	EventFinder( util::id::Ident &id ) : _id(id) {}

	bool operator()( const Ev *ev ) const { return ev->id() == _id; }

	util::id::Ident &_id;

private:
	EventFinder &operator=( const EventFinder & /*ef*/ ) {
		return *this;
	}
};

template<typename Ev, typename V>
struct EventFinderByValue {
	EventFinderByValue( const V &value ) : _value(value) {}
	bool operator()( const Ev *ev ) const { return ev->value() == _value; }
	const V &_value;
};

template<typename Ev, typename V>
inline util::id::Ident startEvent( Ev *ev, bool result, const V &value, std::vector<Ev *> &l ) {
	util::id::Ident	id;
	if (result) {
		ev->value(value);
		l.push_back(ev);
		id=ev->id();
	}
	else {
		LWARN( "System", "Cannot start event" );
		delete ev;
	}
	return id;
}

template<typename Ev, typename V>
inline bool stopEvent( util::id::Ident &id, std::vector<Ev *> &l, V &value ) {
	bool result=false;

	if (util::id::isValid(id)) {
		typename std::vector<Ev *>::iterator it = find_if(
			l.begin(),
			l.end(),
			EventFinder<Ev>(id)
		);
		if (it != l.end()) {
			Ev *ev = (*it);
			value = ev->value();
			delete ev;
			l.erase(it);
			result=true;
		}
		else {
			LWARN( "System", "Cannot stop event" );
		}

		id.reset();
	}
	
	return result;
}

template<typename Ev, typename V>
inline util::id::Ident dispatchEventByValue( std::vector<Ev *> &l, V &value ) {
	util::id::Ident	id;
	typename std::vector<Ev *>::const_iterator it = find_if(
		l.begin(),
		l.end(),
		EventFinderByValue<Ev,V>(value)
	);
	if (it != l.end()) {
		Ev *ev = (*it);
		id = ev->id();
		ev->dispatch();
	}
	else {
		LWARN( "System", "Cannot stop event" );		
	}
	return id;
}

template<typename Ev>
inline util::id::Ident dispatchEvent( std::vector<Ev *> &l, Ev *ev ) {
	util::id::Ident	id;
	typename std::vector<Ev *>::const_iterator it = find(
		l.begin(),
		l.end(),
		ev
	);
	if (it != l.end()) {	//	Is valid?
		id = ev->id();
		ev->dispatch();
	}
	else {
		LWARN( "System", "Cannot stop event" );		
	}
	return id;
}


}
