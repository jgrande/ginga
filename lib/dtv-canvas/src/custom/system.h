#pragma once

#include "../system.h"
#include <util/id/ident.h>

namespace util {
namespace io {
	class Dispatcher;
}
}

namespace canvas {
namespace custom {

class System;
class Timer;

class System : public canvas::System {
public:
	System();
	virtual ~System();

	//	Run/exit system loop
	virtual void run();
	virtual void exit();

	//	IO events
	virtual util::id::Ident addIO( util::DESCRIPTOR fd, const EventCallback &callback );
	virtual void stopIO( util::id::Ident &id );

	//	Timers
	virtual util::id::Ident registerTimer( util::DWORD ms, const EventCallback &callback );
	virtual void unregisterTimer( util::id::Ident &id );

	//	Socket events
	virtual util::id::Ident addSocket( util::SOCKET sock, const EventCallback &callback );
	virtual void stopSocket( util::id::Ident &id );	

protected:
	//	Initialization
	virtual bool init();
	virtual void fin();

	//	Custom initialization
	virtual bool initEvents();
	virtual void finEvents();

	//	Post a event
	virtual void postEvent( const DispatcherTask &task );
	
private:
	util::io::Dispatcher *_io;
};

}
}

