#include "user.h"
#include "../event.h"
#include "../../lua.h"
#include <canvas/system.h>
#include <iostream>

namespace player {
namespace event {
namespace user {

int postEvent( lua_State *st, bool /*isOut*/, int eventPos ) {
	//	Get event module from stack
	Module *module = Module::get( st );
	if (!module) {
		return luaL_error( st, "[event::ncl] Invalid event module" );		
	}

	EventImpl table;
	lua_pushnil(st);  // First key
	while (lua_next(st, eventPos) != 0) {
		const char *key=lua_tostring(st,-2);
		table[key] = EventData(st);
	}

	//	Dispatch table to user
	dispatchUser( module, &table );

	lua_pushboolean( st, 1 );
	return 1;
}

void dispatchUser( Module *module, EventImpl *table ) {
	module->dispatchIn( table );
}

}
}
}
