#include "system.h"
#include "device.h"
#include "input/manager.h"
#include "player/settings.h"
#include <canvas/system.h>
#include <canvas/canvas.h>
#include <util/mcr.h>

namespace player {

System::System()
{
	_input = new input::Manager();
}

System::~System()
{
	delete _input;
	destroy();
}

bool System::canRun() const {
	return !_devices.empty();
}

void System::run() {
	//	Setup reserve keys
	_input->onGlobalKeysChange( boost::bind(&System::onReserveKeys,this,_1) );

	//	Setup devices
	BOOST_FOREACH( Device *dev, _devices ) {
		dev->start();
	}

	//	Run canvas
	canvasSystem()->run();

	//	Stop devices
	BOOST_FOREACH( Device *dev, _devices ) {
		dev->stop();
	}
}

void System::exit() {
	//	Stop canvas
	canvasSystem()->exit();
}

void System::addDevice( Device *dev ) {
	_devices.push_back( dev );
}

void System::destroy( Device *dev ) {
	std::vector<Device *>::iterator it=std::find(
		_devices.begin(), _devices.end(), dev );
	if (it != _devices.end()) {
		destroyDevice( dev );
		_devices.erase( it );
	}
}

void System::destroy() {
	BOOST_FOREACH( Device *dev, _devices ) {
		destroyDevice( dev );
	}
	_devices.clear();
}

void System::destroyDevice( Device *dev ) {
	dev->finalize();
	delete dev;
}

template<typename T>
static Device *findDevice( const std::vector<Device *> &devs, T cmp, int num ) {
	std::vector<Device *>::const_iterator it=devs.begin();
	int i=0;
	while (it != devs.end()) {
		if (cmp((*it))) {
			if (num == i) {
				return (*it);
			}
			else {
				i++;
			}
		}
		it++;
	}
	return NULL;
}

Device *System::getDevice( const std::string &device, int devNumber ) const {
	//	SystemScreen
	size_t found = device.find( "systemScreen" );
	if (found != std::string::npos) {
		return findDevice( _devices, boost::bind(&Device::haveVideo,_1), devNumber );
	}

	//	SystemAudio
	found = device.find( "systemAudio" );
	if (found != std::string::npos) {
		return findDevice( _devices, boost::bind(&Device::haveAudio,_1), devNumber );
	}

	return NULL;
}

void System::onRunTask( canvas::Canvas *canvas, const boost::function<void (void)> &task ) {
	canvas->beginDraw();
	task();
	canvas->endDraw();
}

void System::enqueue( const boost::function<void (void)> &func ) {
	canvasSystem()->enqueue( boost::bind(&System::onRunTask,this,canvasSystem()->canvas(),func) );
}

bool System::dispatchKey( ::util::key::type key, bool isUp ) {
	return _input->dispatchKey( key, isUp );
}

bool System::addInputListener( const input::ListenerId &id, const input::InputCallback &callback, const ::util::key::Keys &keys ) {
	return _input->addInputListener( id, callback, keys );
}

bool System::delInputListener( const input::ListenerId &id ) {
	return _input->delInputListener( id );
}

canvas::System *System::canvasSystem() const {
	assert( _devices[0] );
	return _devices[0]->system();
}

void System::onReserveKeys( const ::util::key::Keys &keys ) {
	BOOST_FOREACH( Device *dev, _devices ) {
		dev->onReserveKeys( keys );
	}
}

//	Editing command
void System::onEditingCommand( const OnEditingCommand &callback ) {
	_onEditingCommand = callback;
}

void System::dispatchEditingCommand( connector::EditingCommandData *event ) {
	if (!_onEditingCommand.empty()) {
		_onEditingCommand( event );
	}
}

//	Timers
util::id::Ident System::registerTimer( ::util::DWORD ms, const canvas::EventCallback &callback ) {
	return canvasSystem()->registerTimer( ms, callback );
}

void System::unregisterTimer( util::id::Ident &timerID ) {
	canvasSystem()->unregisterTimer( timerID );
}

util::id::Ident System::addIO( util::DESCRIPTOR fd, const canvas::EventCallback &callback ) {
	return canvasSystem()->addIO(fd, callback);
}

void System::stopIO( util::id::Ident &id ) {
	canvasSystem()->stopIO( id );
}

//	Socket events
util::id::Ident System::addSocket( util::SOCKET sock, const canvas::EventCallback &callback ) {
	return canvasSystem()->addSocket(sock, callback);	
}

void System::stopSocket( util::id::Ident &id ) {
	canvasSystem()->stopSocket( id );
}


}

