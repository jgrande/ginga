#pragma once

#include "../event.h"

namespace player {
namespace event {
namespace ncl {

//	Event class methods
int postEvent( lua_State *st, bool isOut, int eventPos );
void dispatchPresentation( Module *module, evtAction::type action, const std::string &label );
void dispatchAttribution( Module *module, const std::string &name, evtAction::type action, const std::string &value );

}
}
}
