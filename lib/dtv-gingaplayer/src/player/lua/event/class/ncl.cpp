#include "ncl.h"
#include "../../lua.h"

namespace player {
namespace event {
namespace ncl {

int postEvent( lua_State *st, bool isOut, int eventPos ) {
	//	Get event module from stack
	Module *module = Module::get( st );
	if (!module) {
		return luaL_error( st, "[event::ncl] Invalid event module" );		
	}

	//	Get type of event
	const char* value = lua::getField( st, eventPos, "type" );
	if (!value) {
		return luaL_error( st, "[event::ncl] Invalid type field in event" );
	}
	evtType::type type = getEventType( value );
	if (type == evtType::unknown) {
		return luaL_error( st, "[event::ncl] Invalid type: type=%s\n", value );		
	}

	//	Get action
	value = lua::getField( st, eventPos, "action" );
	if (!value) {
		return luaL_error( st, "[event::ncl] Invalid action field in event" );
	}
	evtAction::type action = getEventAction( value );
	if (action == evtAction::unknown){
		return luaL_error( st, "[event::ncl] Invalid action: action=%s", value );
	}

	switch (type) {
		case evtType::presentation: {
			std::string label = "";
			value = lua::getField( st, eventPos, "label" );
			if (value) {
				label=value;
			}

			if (isOut){
				module->dispatchOut( evtType::presentation, action, label, "" );
			}else{
				dispatchPresentation( st, module, action, label );
			}

			break;
		}
		case evtType::attribution: {
			const char *name = lua::getField( st, eventPos, "name" );
			if (!name) {
				return luaL_error( st, "[event::ncl] Invalid name field in event" );
			}

			value = lua::getField( st, eventPos, "value" );
			if (!value) {
				return luaL_error( st, "[event::ncl] Invalid value field in event" );
			}

			if (isOut){
				module->dispatchOut( evtType::attribution, action, name, value );
			}else{
				dispatchAttribution( st, module, name, action, value );
			}

			break;
		}
		case evtType::selection: {
			value = lua::getField( st, eventPos, "label" );
			if (!value) {
				return luaL_error( st, "[event::ncl] Invalid label field in event" );
			}
			module->dispatchOut( evtType::selection, action, value, "" );
			break;
		}
		default:
			break;
	}

	lua_pushboolean( st, 1 );
	return 1;
}

void dispatchPresentation( lua_State *st, Module *module, evtAction::type action, const std::string &label ) {
	EventImpl event;
	event["class"] = EventData(st, "ncl");
	event["type"] = EventData(st, "presentation");
	event["label"] = EventData(st, label);
	event["action"] = EventData(st, getActionName( action ));
	module->dispatchIn( &event );
}

void dispatchAttribution( lua_State *st, Module *module, const std::string &name, evtAction::type action, const std::string &value ) {
	EventImpl event;
	event["class"] = EventData(st, "ncl");
	event["type"] = EventData(st, "attribution");
	event["name"] = EventData(st, name);
	event["action"] = EventData(st, getActionName( action ));
	event["value"] = EventData(st, value);
	module->dispatchIn( &event );	
}	

}
}
}
