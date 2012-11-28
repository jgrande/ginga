#include "key.h"
#include "../../lua.h"
#include "../../../../input/manager.h"
#include <canvas/system.h>

namespace player {
namespace event {
namespace key {

//	Event key types
enum type {
	unknown = 0,
	press,
	release
};

static type getKeyEventType( const char *name ) {
	if (!strcmp( name, "press" )){
		return press;
	}else if (!strcmp( name, "release" )){
		return release;
	}else{
		return unknown;
	}
}

int postEvent( lua_State *st, bool isOut, int eventPos ) {
	//	Get event type
	const char* value = lua::getField( st, eventPos, "type" );
	if (!value) {
		return luaL_error( st, "[event::key] Invalid type field in event" );
	}
	type type = getKeyEventType( value );

	if (type != unknown) {
		//	Get key field
		value = lua::getField( st, eventPos, "key" );
		if (!value) {
			return luaL_error( st, "[event::key] Invalid key field in event" );
		}
		util::key::type key = util::key::getKey( value );

		if (key != util::key::null){
			//	Get event module from stack
			Module *module = Module::get( st );
			if (!module) {
				return luaL_error( st, "[player::event::key] Invalid event module" );		
			}

			if (isOut) {
				module->dispatchKey( st, key, type == release );
			}
			else {				
				dispatchKey( st, module, key, type == release );
			}

		} else {
			return luaL_error( st, "[player::event::key], Invalid key: key=%s", value );
		}

	} else {
		return luaL_error( st, "[player::event::key] Invalid type: type=%s", value );
	}

	lua_pushboolean( st, 1 );
	return 1;
}

void dispatchKey( lua_State *st, Module *module, util::key::type key, bool isUp ) {
	EventImpl event;
	event["class"] = EventData(st, "key");
	event["type"] = EventData(st, isUp ? "release" : "press");
	event["key"] = EventData(st, util::key::getKeyName( key ));
	module->dispatchIn( &event );
}

}
}
}
