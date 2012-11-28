#pragma once

#include <boost/function.hpp>
#include <string>
#include <map>

namespace player {
namespace event {

//	Event type
#define TYPE_LIST(fnc)	\
	fnc( presentation )	\
	fnc( selection )	\
	fnc( attribution )

namespace evtType {
#define DO_ENUM_TYPE(t) t,
enum type {
	unknown = 0,
	TYPE_LIST(DO_ENUM_TYPE)
	LAST
};
#undef DO_ENUM_TYPE
}

//	Event action
#define ACTION_LIST(fnc)	\
	fnc( start )	\
	fnc( stop )		\
	fnc( abort )	\
	fnc( pause )	\
	fnc( resume )

namespace evtAction {
#define DO_ENUM_ACTION(a) a,
enum type {
	unknown = 0,
	ACTION_LIST(DO_ENUM_ACTION)
	LAST
};
#undef DO_ENUM_ACTION
}

//	Event
class EventData;
typedef std::map<std::string, EventData> EventImpl;

//	Callbacks
typedef boost::function<void(
	evtType::type type,
	evtAction::type action,
	const std::string &parameter,
	const std::string &value)> Callback;

typedef boost::function<void ( EventImpl * )> InputCallback;

class Module;

//	getters
evtType::type getEventType( const char *name );
evtAction::type getEventAction( const char *name );
const char *getActionName( evtAction::type action );

}
}
