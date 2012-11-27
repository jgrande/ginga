#pragma once

#include "../../system.h"
#include <queue>
#include <vector>

namespace util {
	class Task;
}

struct _GIOChannel;
typedef struct _GIOChannel GIOChannel;

namespace canvas {
namespace gtk {

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

	//	Instance creation
	virtual WebViewer *createWebViewer( Surface * );

	//	Aux
	typedef Event<int> Timer;
	typedef std::vector<Timer *> TimerList;
	typedef Event<int> IOEvent;
	typedef std::vector<IOEvent *> IOList;
	void onKeyEvent( util::key::type keyValue, bool isUp );
	void onTaskEvent();
	void onDispatchTimer( Timer *timer );
	void onDispatchIO( IOEvent *io );	
	void onWindowDestroyed( void );

protected:
	//	Initialization
	virtual bool init();	
	virtual void fin();

	//	Instance creation
	virtual canvas::Window *createWindow() const;
	virtual canvas::Canvas *createCanvas() const;

	//	Aux tasks
	virtual void postEvent( const DispatcherTask &task );
	void doExit();

private:
	util::id::Pool *_pool;
	int _idleFunc;
	std::queue<util::Task *> _tasks;
	TimerList _timerList;
	IOList _ioList;
	boost::mutex _mutex;
};

}
}

