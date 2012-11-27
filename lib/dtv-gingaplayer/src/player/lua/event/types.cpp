#include "types.h"

namespace player {
namespace event {

#define DO_ENUM_TYPE_STRING( t ) #t,
static const char* types[] = {
    "NULL",
    TYPE_LIST(DO_ENUM_TYPE_STRING)
    "LAST"
};

#define DO_ENUM_ACTION_STRING( a ) #a,
static const char* actions[] = {
    "NULL",
    ACTION_LIST(DO_ENUM_ACTION_STRING)
    "LAST"
};
#undef DO_ENUM_PROPERTY_STRING

evtType::type getEventType( const char *name ) {
	for (int i=0; i<evtType::LAST; i++) {
		if (!strncmp( types[i], name, strlen(types[i]) )) {
			return (evtType::type)i;
		}
	}
	return evtType::unknown;
}

evtAction::type getEventAction( const char *name ){
	for (int i=0; i<evtAction::LAST; i++) {
		if (!strncmp( actions[i], name, strlen(actions[i]) )) {
			return (evtAction::type)i;
		}
	}
	return evtAction::unknown;
}

const char *getActionName( evtAction::type action ) {
	if (action > evtAction::LAST) {
		action=evtAction::unknown;
	}
	return actions[action];
}

}
}
