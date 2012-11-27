#pragma once

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

namespace player {
namespace lua {

void storeObject( lua_State *st, void *obj, const char *index );

template<class T>
inline T *getObject( lua_State *st, const char *index  ) {
	lua_getfield( st, LUA_REGISTRYINDEX, index );
	T *obj = (T *) lua_touserdata( st, -1 );
	lua_pop( st, 1 );
	return obj;
}

const char *getField( lua_State *st, int pos, const char *index );

}
}

