#include "system.h"
#include <util/log.h>
#include <util/io/dispatcher.h>
#include <util/mcr.h>
#include <boost/foreach.hpp>

namespace canvas {
namespace custom {

System::System() {
	_io = util::io::Dispatcher::create();
}

System::~System() {
	DEL(_io);
}

//	Initialization
bool System::init() {
	LINFO("custom::System", "Init");

	if (!_io->initialize()) {
		DEL(_io);
		return false;
	}

	//	Initialize events
	if (!initEvents()) {
		DEL(_io);
		return false;
	}

	return true;
}

void System::fin() {
	LINFO("custom::System", "Fin");
	finEvents();
	_io->finalize();
}

bool System::initEvents() {
	return true;
}

void System::finEvents() {
}

//	Post a event
void System::postEvent( const DispatcherTask &task ) {
	_io->postEvent( task );
}

//	Run/exit system loop
void System::run() {
	assert(_io);
	_io->run();	
}

void System::exit() {
	assert(_io);	
	_io->exit();
}

//	IO
util::id::Ident System::addIO( util::DESCRIPTOR fd, const EventCallback &callback ) {
	return _io->addIO( fd, callback );
}

void System::stopIO( util::id::Ident &id ) {
	_io->stopIO( id );
}

//	Timers
util::id::Ident System::registerTimer( util::DWORD ms, const EventCallback &callback ) {
	return _io->addTimer( ms, callback );
}

void System::unregisterTimer( util::id::Ident &id ) {
	_io->stopTimer( id );
}

//	Socket events
util::id::Ident System::addSocket( util::SOCKET sock, const EventCallback &callback ) {
	return _io->addSocket( sock, callback );
}

void System::stopSocket( util::id::Ident &id ) {
	_io->stopSocket( id );
}

}
}
