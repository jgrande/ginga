#pragma once

#include "../event.h"

namespace player {
namespace event {
namespace tcp {

//	Event class methods
int postEvent( lua_State *st, bool isOut, int eventPos );
void onDataReceived( Module *module, const std::string &val, int socketID);

}
}
}

