#pragma once

#include "../event.h"

namespace player {
namespace event {
namespace user {

//	Event class methods
int postEvent( lua_State *st, bool isOut, int eventPos );
void dispatchUser( Module *module, EventImpl *table );

}
}
}

