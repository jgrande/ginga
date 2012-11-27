#include "lua.h"
#include "../luaplayer.h"

namespace player {
namespace lua {

void storeObject( lua_State *st, void *obj, const char *index ) {
	lua_pushlightuserdata( st, obj );
	lua_setfield( st, LUA_REGISTRYINDEX, index );
}

const char *getField( lua_State *st, int pos, const char *szIndex ) {
	lua_getfield( st, pos, szIndex );
	if (lua_isnil(st, -1)) {
		return NULL;
	}
	return luaL_checkstring( st, -1 );
}


}
}

