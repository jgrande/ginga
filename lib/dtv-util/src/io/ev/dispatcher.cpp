/*******************************************************************************

  Copyright (C) 2010, 2011 LIFIA - Facultad de Informatica - Univ. Nacional de La Plata

********************************************************************************

  This file is part of DTV-util implementation.

    DTV-util is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by the Free
  Software Foundation, either version 2 of the License.

    DTV-util is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with
  this program. If not, see <http://www.gnu.org/licenses/>.

********************************************************************************

  Este archivo es parte de la implementación de DTV-util.

    DTV-util es Software Libre: Ud. puede redistribuirlo y/o modificarlo
  bajo los términos de la Licencia Pública General Reducida GNU como es publicada por la
  Free Software Foundation, según la versión 2 de la licencia.

    DTV-util se distribuye esperando que resulte de utilidad, pero SIN NINGUNA
  GARANTÍA; ni siquiera la garantía implícita de COMERCIALIZACIÓN o ADECUACIÓN
  PARA ALGÚN PROPÓSITO PARTICULAR. Para más detalles, revise la Licencia Pública
  General Reducida GNU.

    Ud. debería haber recibido una copia de la Licencia Pública General Reducida GNU
  junto a este programa. Si no, puede verla en <http://www.gnu.org/licenses/>.

*******************************************************************************/

#include "dispatcher.h"
#include "../../log.h"
#include "../../task.h"
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <ev.h>

#define INIT(data,callback)	\
	assert( !callback.empty() ); \
	data.callback = callback; \
	data.id = allocID();	\
	LDEBUG("io::ev::Dispatcher", "Init event: id=%ld", data.id->getID());

#define STOP_EVENT(t, l, id, method)	\
	std::list<t *>::iterator it=std::find_if( l.begin(), l.end(), impl::EventFinder<t>(id) ); \
	if (it != l.end()) { \
		t *ev=(*it); \
		l.erase(it); \
		ev_##method##_stop( _loop, &ev->ev ); \
		ev->data.id.reset(); \
		free( ev ); \
	} \
	else { LWARN("io::ev::Dispatcher", "invalid " #method ": %ld", id); }

namespace util {
namespace io {
namespace ev {

namespace impl {

struct my_data {
	id::Ident id;
	io::Dispatcher::Callback callback;
};
	
struct my_timer_ev {
	struct ev_timer ev;
	struct my_data data;
};

struct my_io_ev {
	struct ev_io ev;
	struct my_data data;	
};

static void wakeup_cb( struct ev_loop *loop, struct ev_async */*w*/, int /*revents*/ ) {
	Dispatcher *sys = (Dispatcher *)ev_userdata(loop);
	assert(sys);	
	sys->wakeup();
}

static void timer_cb( struct ev_loop *loop, struct ev_timer *timer, int /*revents*/ ) {
	Dispatcher *sys = (Dispatcher *)ev_userdata(loop);
	assert(sys);
	struct my_timer_ev *ev = (struct my_timer_ev *)timer;
	util::id::Ident id(ev->data.id);
	ev->data.callback( id );	
	sys->stopTimer( id );
}

static void io_cb( struct ev_loop */*loop*/, struct ev_io *w, int /*revents*/ ) {
	struct my_io_ev *ev = (struct my_io_ev *)w;
	ev->data.callback( ev->data.id );	
}

template<class T>
class EventFinder {
public:
	EventFinder( id::ID_TYPE id ) : _id(id) {}
	
	bool operator()( const T *io ) const {
		return io->data.id->getID() == _id;
	}

private:
	id::ID_TYPE _id;
};

}

Dispatcher::Dispatcher()
{
	_loop = NULL;
	_wakeup = NULL;
	_threadID = boost::this_thread::get_id();
}

Dispatcher::~Dispatcher()
{
}

//	Initialization
bool Dispatcher::initialize() {
	//	Create loop
	_loop = ev_loop_new(EVFLAG_AUTO);
	if (!_loop) {
		LERROR("io::ev::Dispatcher", "cannot create loop");
		return false;
	}
	ev_set_userdata( _loop, this );

	//	Create and initialize wakeup watcher
	_wakeup = (ev_async *)malloc( sizeof(struct ev_async) );
	if (!_wakeup) {
		free(_loop);
		LWARN("io::ev::Dispatcher", "cannot create async event");
		return false;
	}
	ev_async_init (_wakeup, impl::wakeup_cb);
	ev_async_start (_loop, _wakeup);

	return true;
}

void Dispatcher::finalize() {
	//	Run all tasks in queue
	while (!_tasks.empty()) {
		Task *task = _tasks.front();
		_tasks.pop();
		runTask( task );
	}

	//	Cleanup all events
	while (!_io.empty()) {
		ListOfIO::iterator it = _io.begin();
		LWARN("io::ev::Dispatcher", "stopping lost io event: fd=%d", (*it)->ev.fd);
		stopIOImpl( (*it)->data.id->getID() );
	}

	while (!_timers.empty()) {
		ListOfTimer::iterator it = _timers.begin();
		LWARN("io::ev::Dispatcher", "stopping lost timer event");
		stopTimerImpl( (*it)->data.id->getID() );
	}

	//	Destroy loop
	ev_loop_destroy( _loop );
	_loop = NULL;
	free(_wakeup);
	_wakeup = NULL;
}

void Dispatcher::run() {
	LINFO( "util::io::ev::Dispatcher", "Run begin" );

	//	Setup threadID
	_threadID = boost::this_thread::get_id();	

	//	Wait for events to arrive
	ev_run (_loop, 0);

	LINFO( "util::io::ev::Dispatcher", "Run end" );	
}

void Dispatcher::exit() {
	LINFO( "util::io::ev::Dispatcher", "Exit" );		

	//	Stop loop
	dispatchTask( boost::bind(&Dispatcher::exitLoop, this) );
}

//	Post a event
void Dispatcher::postEvent( const DispatcherTask &task ) {
	dispatchTask( task, true );
}

//	Timer events
id::Ident Dispatcher::addTimer( int ms, const Callback &callback ) {
	LDEBUG("io::ev::Dispatcher", "Add timer: ms=%d", ms);

	//	Create timer
	struct impl::my_timer_ev *timer = (struct impl::my_timer_ev *)calloc( 1, sizeof(struct impl::my_timer_ev) );
	if (!timer) {
		LERROR("io::ev::Dispatcher", "cannot create timer event");
		return id::Ident();
	}
	else {
		//	Setup
		INIT( timer->data, callback );

		{
			struct ev_timer *ev = &timer->ev;
			ev_timer_init( ev, impl::timer_cb, ms/1000., 0. );
		}

		//	Add to loop
		dispatchTask( boost::bind(&Dispatcher::startTimer, this, timer ) );

		return timer->data.id;
	}
}

void Dispatcher::startTimer( struct impl::my_timer_ev *timer ) {
	ev_timer_start (_loop, &timer->ev);
	_timers.push_back( timer );
}

void Dispatcher::stopTimer( id::Ident &id ) {
	if (util::id::isValid(id)) {
		dispatchTask( boost::bind(&Dispatcher::stopTimerImpl, this, id->getID() ) );
		id.reset();
	}
}

void Dispatcher::stopTimerImpl( id::ID_TYPE id ) {
	STOP_EVENT( struct impl::my_timer_ev, _timers, id, timer );	
}

//	IO events
id::Ident Dispatcher::addIO( DESCRIPTOR fd, const Callback &callback ) {
	struct impl::my_io_ev *io = (struct impl::my_io_ev *)calloc( 1, sizeof(struct impl::my_io_ev) );
	if (!io) {
		LERROR("io::ev::Dispatcher", "cannot create io event");
		return id::Ident();
	}
	else {
		//	Setup
		INIT( io->data, callback );

		{
			struct ev_io *ev = &io->ev;
			ev_io_init( ev, impl::io_cb, fd, EV_READ );
		}

		//	Add to loop
		dispatchTask( boost::bind(&Dispatcher::startIO, this, io ) );

		return io->data.id;
	}
}
	
void Dispatcher::stopIO( id::Ident &id ) {
	if (util::id::isValid(id)) {
		dispatchTask( boost::bind(&Dispatcher::stopIOImpl, this, id->getID() ) );
		id.reset();
	}
}

void Dispatcher::startIO( struct impl::my_io_ev *io ) {
	ev_io_start (_loop, &io->ev);
	_io.push_back( io );
}

void Dispatcher::stopIOImpl( id::ID_TYPE id ) {
	STOP_EVENT( struct impl::my_io_ev, _io, id, io );
}

//	Socket events
id::Ident Dispatcher::addSocket( SOCKET sock, const Callback &callback ) {
	return addIO( sock, callback );
}

void Dispatcher::stopSocket( id::Ident &id ) {
	stopIO( id );
}

//	Aux
void Dispatcher::wakeup() {
	util::Task *task;
	std::vector<util::Task *> tasks;

	//	Get all task to run
	_mutex.lock();
	while (!_tasks.empty()) {
		task = _tasks.front();
		_tasks.pop();
		tasks.push_back( task );
	}
	_mutex.unlock();

	//	Run tasks
	BOOST_FOREACH( util::Task *task, tasks ) {
		runTask( task );
	}
}

void Dispatcher::runTask( Task *task ) {
	try {
		task->run();
	} catch ( const std::exception &e ) {
		LWARN("io::ev::Dispatcher", "Catch exception: %s", e.what());
	}
	delete task;
}

void Dispatcher::dispatchTask( const boost::function<void (void)> &fnc, bool enqueue/*=false*/ ) {
	_mutex.lock();
	_tasks.push( new util::BasicTask(fnc) );
	_mutex.unlock();
	
	if (enqueue || boost::this_thread::get_id() != _threadID) {
		//	Stop loop
		ev_async_send( _loop, _wakeup );
	}
	else {
		wakeup();
	}
}

void Dispatcher::exitLoop() {
	ev_break( _loop );
}

}
}
}

