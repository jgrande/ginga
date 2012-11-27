#include "input.h"
#include "system.h"
#include "generated/config.h"
#if SYS_INPUT_USE_LIRC
#       include "impl/lirc/inputlirc.h"
#endif
#if SYS_INPUT_USE_LINUX
#       include "impl/linux/inputlinux.h"
#endif
#include <util/mcr.h>
#include <util/cfg/configregistrator.h>
#include <assert.h>

REGISTER_INIT_CONFIG( gui_input ) {
	root().addNode( "input" );
}

namespace canvas {

void Input::create( System *sys ) {
	assert(sys);
	UNUSED(sys);
#if SYS_INPUT_USE_LIRC
	bool uselirc = util::cfg::getValue<bool> ("gui.input.lirc");
	if (uselirc) {
		sys->addInput( new input::lirc::InputLIRC(sys) );
	}
#endif
#if SYS_INPUT_USE_LINUX
	bool uselinux = util::cfg::getValue<bool> ("gui.input.linux.enabled");
	if (uselinux) {
		sys->addInput( new input::event::InputLinux(sys) );
	}
#endif
}

Input::Input( System *sys )
	: _sys( sys )
{
}

Input::~Input() {
}

bool Input::initialize() {
	return true;
}

void Input::finalize() {
}

System *Input::sys() const {
	return _sys;
}

}

