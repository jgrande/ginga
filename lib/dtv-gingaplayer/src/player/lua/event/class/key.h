#pragma once

#include "../event.h"

namespace player {
namespace event {
namespace key {

//	Event class methods
int postEvent( lua_State *st, bool isOut, int eventPos );
void dispatchKey( lua_State *st, Module *module, util::key::type key, bool isUp );

}
}
}

