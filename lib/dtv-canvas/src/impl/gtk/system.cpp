#include "system.h"
#include "window.h"
#include "webviewer.h"
#include "videooverlay.h"
#include "../cairo/canvas.h"
#include "../../event.h"
#include "generated/config.h"
#include <util/id/pool.h>
#include <util/task.h>
#include <util/log.h>
#include <util/mcr.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

namespace canvas {
namespace gtk {

namespace impl {

static System *sys = NULL;

System *getSystem() {
	assert(impl::sys);
	return impl::sys;
}

static gboolean ev_rcv( GIOChannel * /*chan*/, GIOCondition /*condition*/, System::IOEvent *io ) {
	assert(io);
	getSystem()->onDispatchIO( io );
	return TRUE;
}

static gboolean timeoutCallback( System::Timer *timer ) {
	assert(timer);
	getSystem()->onDispatchTimer( timer );
	return FALSE;
}

static gboolean onTaskCallback( System *sys ) {
	assert(sys);
	sys->onTaskEvent();
	return FALSE;
}

}	//	namespace impl


System::System()
{
	_idleFunc = -1;
	impl::sys = this;
	_pool = new util::id::Pool("gtk");
}

System::~System()
{
	delete _pool;
	impl::sys = NULL;
}

//	Initialization
bool System::init() {
	//	Initialize glib
	if (!g_thread_supported ()) {
		g_thread_init (NULL);
	}
	gdk_threads_init ();
	gtk_init(NULL, NULL);

	return true;
}

void System::fin() {
	util::Task *task;
	_mutex.lock();
	while (!_tasks.empty()) {
		task = _tasks.front();
		_tasks.pop();
		delete task;
	}
	_mutex.unlock();	
}

//	Run/exit system loop
void System::run() {
	LINFO("gtk::System", "Main loop begin");
	
	gdk_threads_enter ();

	//	Run loop
	gtk_main();

	gdk_threads_leave ();

	LINFO("gtk::System", "Main loop end");
}

void System::exit() {
	//	Wakeup thread
	postEvent( boost::bind(&System::doExit,this) );
}

void System::doExit() {
	gtk_main_quit();
}

//	IO events
util::id::Ident System::addIO( util::DESCRIPTOR fd, const EventCallback &callback ) {
#ifdef _WIN32
	UNUSED(fd);
	UNUSED(callback);
	return util::id::Ident();
#else
	IOEvent *ev = new IOEvent(_pool->alloc(),callback);
	GIOChannel *chan = g_io_channel_unix_new(fd);
	int watchID=g_io_add_watch( chan, (GIOCondition) (G_IO_IN | G_IO_PRI), (GIOFunc)impl::ev_rcv, (gpointer)ev );
	g_io_channel_unref( chan );
	return startEvent( ev, watchID != 0, watchID, _ioList );
#endif
}
	
void System::stopIO( util::id::Ident &id ) {
	int watchID;
	if (stopEvent( id, _ioList, watchID )) {
		g_source_remove( watchID );
	}
}

void System::onDispatchIO( IOEvent *io ) {
	dispatchEvent( _ioList, io );
}

//	Socket events
util::id::Ident System::addSocket( util::SOCKET sock, const EventCallback &callback ) {
#ifdef _WIN32
	IOEvent *ev = new IOEvent(_pool->alloc(),callback);
	GIOChannel *chan = g_io_channel_win32_new_socket (sock);
	int watchID=g_io_add_watch( chan, (GIOCondition) (G_IO_IN | G_IO_PRI), (GIOFunc)impl::ev_rcv, (gpointer)ev );
	g_io_channel_unref( chan );
	return startEvent( ev, watchID != 0, watchID, _ioList );
#else	
	return addIO( sock, callback );
#endif
}

void System::stopSocket( util::id::Ident &id ) {
	stopIO( id );
}

//	Timers
util::id::Ident System::registerTimer( util::DWORD ms, const EventCallback &callback ) {
	Timer *ev = new Timer(_pool->alloc(), callback);
	int id=g_timeout_add( ms, (GSourceFunc)impl::timeoutCallback, (gpointer)ev );
	return startEvent( ev, id != 0, id, _timerList );
}

void System::unregisterTimer( util::id::Ident &id ) {
	int timerID;
	if (stopEvent( id, _timerList, timerID )) {
		g_source_remove( timerID );
	}
}

void System::onDispatchTimer( Timer *timer ) {
	//	Two pass, becouse in dispatch callback can unregister timer!
	util::id::Ident id=dispatchEvent( _timerList, timer );
	unregisterTimer( id );
}

//	Instance creation
canvas::WebViewer *System::createWebViewer( Surface *surface ) {
#if SYS_HTML_USE_GTK
	return new WebViewer( (canvas::System *)this, surface );
#else
	return canvas::System::createWebViewer( surface );
#endif
}

canvas::Canvas *System::createCanvas() const {
	return new cairo::Canvas();
}

canvas::Window *System::createWindow() const {
	return new Window();
}
	 
void System::onKeyEvent( util::key::type keyValue, bool isUp ) {
	dispatchKey( keyValue, isUp );
}

void System::onTaskEvent() {
	util::Task *task;
	std::vector<util::Task *> tasks;
	
	//	Get tasks to run
	_mutex.lock();
	while (!_tasks.empty()) {
		task = _tasks.front();
		_tasks.pop();
		tasks.push_back( task );
	}
	_mutex.unlock();	

	//	Run tasks
	BOOST_FOREACH( util::Task *task, tasks ) {
		try {
			task->run();
		} catch ( const std::exception &e ) {
			LWARN("gtk::System", "Catch exception: %s", e.what());
		}
		delete task;
	}
}

void System::onWindowDestroyed( void ) {
	windowDestroyed();
}

//	Aux tasks
void System::postEvent( const DispatcherTask &task ) {
	_mutex.lock();
	_tasks.push( new util::BasicTask(task) );
	_mutex.unlock();

	g_timeout_add( 1, (GSourceFunc)impl::onTaskCallback, (gpointer)this );	
}

}
}
