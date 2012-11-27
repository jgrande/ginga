#include "ginga.h"
#include "util.h"
#include <ncl30-presenter/presentationenginemanager.h>
#include <gingaplayer/system.h>
#include <canvas/canvas.h>
#include <canvas/system.h>
#include <gingaplayer/device.h>
#include <util/mcr.h>
#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;
namespace bptgn = br::pucrio::telemidia::ginga::ncl;

namespace ginga {

namespace impl {
	static player::System *sys;
	static bptgn::PresentationEngineManager* pem;
}

void init() {
	//	Init sys
	impl::sys = new player::System();
	player::Device *dev=new player::Device( impl::sys );
	dev->initialize();
	impl::sys->addDevice( dev );

	//	Init PEM
	impl::pem = new bptgn::PresentationEngineManager( impl::sys );
}

void fin() {
	DEL( impl::pem );
	DEL( impl::sys );
}

void run() {
	impl::pem->run();
}

void stop() {
	impl::sys->exit();
}

Ginga::Ginga() {
	_compare = false;
	_keyPressed = false;
	_compareReady = false;
}

Ginga::~Ginga() {
}

void Ginga::SetUp( void ) {
	assert( impl::pem );
	bptgn::PresentationEngineManager::onKeyPress( boost::bind( &Ginga::onKeyPressed, this, _1 ) );
}

void Ginga::TearDown( void ) {
	bptgn::PresentationEngineManager::onKeyPress( NULL );
}

bool Ginga::play( const std::string &file ) {
	fs::path url( util::getTestRoot() );
	url /= "src";
	url /= "ncl";
	url /= file;

	if (exists( url ) && is_regular_file( url )) {
		return impl::pem->startDocument( url.string() );
	}

	return false;
}

canvas::Canvas *Ginga::canvas( void ) {
	return impl::pem->mainScreen()->system()->canvas();
}

//	Compare
static boost::condition_variable _compareWakeup;
static boost::mutex _compareMutex;

bool Ginga::compareTo( const std::string &file ) {
	_file = file;
	impl::pem->enqueue( boost::bind( &Ginga::compare, this ) );

	{ //	Wait for compare
		boost::unique_lock<boost::mutex> lock( _compareMutex );
		while (!_compareReady) {
			_compareWakeup.wait( lock );
		}
		_compareReady = false;
	}
	return _compare;
}

void Ginga::compare( void ) {
	_compareMutex.lock();
	_compare = util::compareImages( canvas(), _file );
	_compareReady = true;
	_compareMutex.unlock();
	_compareWakeup.notify_one();
}

//	Key press
static boost::condition_variable _keyWakeup;
static boost::mutex _keyMutex;

bool Ginga::pressKey( ::util::key::type key ) {
	impl::pem->enqueue( boost::bind( &player::Device::dispatchKey, impl::pem->mainScreen(), key, false ) );
	{ //	Wait for compare
		boost::unique_lock<boost::mutex> lock( _keyMutex );
		while (!_keyPressed) {
			_keyWakeup.wait( lock );
		}
		_keyPressed = false;
	}
	return true;
}

void Ginga::onKeyPressed( ::util::key::type /*key*/) {
	_keyMutex.lock();
	_keyPressed = true;
	_keyMutex.unlock();
	_keyWakeup.notify_one();
}

}
