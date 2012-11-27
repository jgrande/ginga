#include "system.h"
#include "../../src/system.h"
#include "../../src/canvas.h"
#include "generated/config.h"
#include <util/mcr.h>
#include <util/types.h>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

namespace impl {

	typedef std::pair<util::key::type, bool> KeyStored;
	std::vector<KeyStored> _keys;
	boost::condition_variable wakeup;
	boost::mutex mutex;

	static void inputCallback( util::key::type keyValue, bool isUp ) {
		_keys.push_back( std::make_pair(keyValue,isUp) );
		if (keyValue == util::key::f1) {
			impl::wakeup.notify_all();
		}
	}

	void init( const std::string &name ) {
		canvas::System *sys = canvas::System::create( name );
		sys->setInputCallback( boost::bind(&inputCallback, _1, _2) );
		sys->initialize();
		System::setSystem(sys);
	}

	void fin() {
		System::getSystem()->finalize();
		delete System::getSystem();
		System::setSystem(NULL);
	}

}

canvas::System* System::_system;

canvas::System *System::getSystem() {
	return _system;
}

void System::setSystem( canvas::System *sys ) {
	_system = sys;
}

TEST_F( System, canvas_exist ) {
	ASSERT_TRUE( getSystem()->canvas() != NULL );
}

TEST_F( System, DISABLED_keys ) {
	printf( "Press F1\n" );
	{	//	Wait for key!
		boost::unique_lock<boost::mutex> lock( impl::mutex );
		impl::wakeup.wait(lock);
	}

	ASSERT_TRUE( impl::_keys.size() > 0 );
	bool pressed=false;
	for (size_t i=0; i<impl::_keys.size(); i++) {
		if (impl::_keys[i].first == util::key::f1) {
			pressed=true;
		}
	}
	ASSERT_TRUE( pressed );
}

static void timerCallback( int *count, util::id::Ident &/*id*/ ) {
	(*count)++;
	impl::wakeup.notify_all();
}

TEST_F( System, DISABLED_timer_attach ) {
	int count=0;
	util::id::Ident id = getSystem()->registerTimer( 10, boost::bind(&timerCallback,&count,_1) );
	ASSERT_TRUE( util::id::isValid(id) );
	
	{	//	Wait for timer!
		boost::unique_lock<boost::mutex> lock( impl::mutex );
		impl::wakeup.wait(lock);
	}

	ASSERT_TRUE( count == 1 );
}

TEST_F( System, DISABLED_timer_queue_attach ) {
	//TODO: getSystem()->setDispatcher( &dispatch );
	
	int count=0;
	util::id::Ident id = getSystem()->registerTimer( 10, boost::bind(&timerCallback,&count,_1) );
	ASSERT_TRUE(util::id::isValid(id));
	
	{	//	Wait for timer!
		boost::unique_lock<boost::mutex> lock( impl::mutex );
		impl::wakeup.wait(lock);
	}

	ASSERT_TRUE( count == 1 );
}


TEST_F( System, DISABLED_timer_cancel ) {
	int count=0;
	util::id::Ident id = getSystem()->registerTimer( 10000, boost::bind(&timerCallback,&count,_1) );
	ASSERT_TRUE( util::id::isValid(id) );

	getSystem()->unregisterTimer( id );
	ASSERT_TRUE( count == 0 );
}

TEST_F( System, DISABLED_timer_queue_cancel ) {
	int count=0;
	util::id::Ident id = getSystem()->registerTimer( 10000, boost::bind(&timerCallback,&count,_1) );
	ASSERT_TRUE( util::id::isValid(id) );

	getSystem()->unregisterTimer( id );
	ASSERT_TRUE( count == 0 );
}
