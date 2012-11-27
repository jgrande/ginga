#include "../util.h"
#include "../../../src/input/input.h"
#include "../../../src/input/manager.h"
#include <boost/foreach.hpp>
#include <vector>
#include <util/mcr.h>

class InputTest : public testing::Test {
public:
	InputTest() {}
	virtual ~InputTest() {}

protected:
	virtual void SetUp( void ) {
		_input = new player::input::Manager();
	}

	virtual void TearDown( void ) {
		DEL(_input);
	}

	player::input::Manager *_input;
};

class Listener
{
public:
	Listener( player::input::Manager *input )
		: _input(input)
	{
		_callbacksCount = 0;
	}

	virtual ~Listener() {}

	bool init(  ) {
		player::input::InputCallback c = boost::bind( &Listener::onKey, this, _1, _2 );
		return _input->addInputListener( this, c, _keys );
	}

	bool fin() {
		return _input->delInputListener( this );
	}

	void onKey( ::util::key::type /*key*/, bool /*isUp*/) {
		_callbacksCount ++;

		BOOST_FOREACH( Listener *listener, _listenersToDel ){
			listener->fin();
		}

		BOOST_FOREACH( Listener *listener, _listenersToAdd ){
			listener->init();
		}
	}

	void onKeyDel( Listener *listener ) {
		_listenersToDel.push_back( listener );
	}

	void onKeyAdd( Listener *listener ) {
		_listenersToAdd.push_back( listener );
	}

	int callbacksCount( void ) {
		return _callbacksCount;
	}
	
	void setKeys( ::util::key::Keys &keys ) {
		_keys = keys;
	}

private:
	player::input::Manager *_input;
	std::vector<Listener*> _listenersToDel;
	std::vector<Listener*> _listenersToAdd;
	int _callbacksCount;
	::util::key::Keys _keys;
};

TEST_F( InputTest, basic )
{
	Listener *listener = new Listener( _input );
	
	ASSERT_TRUE( listener->init() );
	ASSERT_TRUE( listener->fin() );
	ASSERT_TRUE( listener->callbacksCount() == 0 );
}

TEST_F( InputTest, no_keys )
{
	Listener *listener = new Listener( _input );
	ASSERT_TRUE( listener->init() );
	ASSERT_TRUE( listener->callbacksCount() == 0 );
	
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	
	ASSERT_TRUE( listener->callbacksCount() == 0 );
	ASSERT_TRUE( listener->fin() );
}

TEST_F( InputTest, no_listener )
{
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
}

TEST_F( InputTest, wrong_key )
{
	::util::key::Keys keys;
	keys.insert(::util::key::green);
	
	Listener *listener = new Listener( _input );
	listener->setKeys(keys);
	ASSERT_TRUE( listener->init() );
	
	ASSERT_TRUE( listener->callbacksCount() == 0 );
	
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	
	ASSERT_TRUE( listener->callbacksCount() == 0 );
	ASSERT_TRUE( listener->fin() );
}

TEST_F( InputTest, multiple_listeners )
{
	::util::key::Keys keys;
	keys.insert(::util::key::green);
	
	Listener *listener = new Listener( _input );
	listener->setKeys(keys);
	ASSERT_TRUE( listener->init() );
	
	::util::key::Keys keys2;
	keys2.insert(::util::key::green);
	keys2.insert(::util::key::red);
	
	Listener *listener2 = new Listener( _input );
	listener2->setKeys(keys2);
	ASSERT_TRUE( listener2->init() );
	
	ASSERT_TRUE( listener->callbacksCount() == 0 );
	ASSERT_TRUE( listener2->callbacksCount() == 0 );
	
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	ASSERT_TRUE( listener->callbacksCount() == 0 );
	ASSERT_TRUE( listener2->callbacksCount() == 1 );
	
	ASSERT_TRUE( _input->dispatchKey( ::util::key::green, true ) );
	ASSERT_TRUE( listener->callbacksCount() == 1 );
	ASSERT_TRUE( listener2->callbacksCount() == 2 );
	ASSERT_TRUE( listener->fin() );
	ASSERT_TRUE( listener2->fin() );
}

TEST_F( InputTest, cursor_key )
{
	::util::key::Keys keys;
	keys.insert(::util::key::cursor_down);
	keys.insert(::util::key::cursor_up);
	keys.insert(::util::key::cursor_left);
	keys.insert(::util::key::cursor_right);
	
	Listener *listener = new Listener( _input );
	listener->setKeys(keys);
	ASSERT_TRUE( listener->init() );
	
	ASSERT_TRUE( listener->callbacksCount() == 0 );
	
	ASSERT_TRUE( _input->dispatchKey( ::util::key::cursor_down, true ) );
	ASSERT_TRUE( _input->dispatchKey( ::util::key::cursor_left, true ) );
	ASSERT_TRUE( _input->dispatchKey( ::util::key::cursor_right, true ) );
	ASSERT_TRUE( _input->dispatchKey( ::util::key::cursor_up, true ) );
	
	ASSERT_TRUE( listener->callbacksCount() == 4 );
	ASSERT_TRUE( listener->fin() );
}

TEST_F( InputTest, dispatch )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);
	Listener *listener = new Listener( _input );
	
	listener->setKeys(keys);
	ASSERT_TRUE( listener->init() );
	ASSERT_TRUE( listener->callbacksCount() == 0 );

	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );

	ASSERT_TRUE( listener->callbacksCount() == 1 );
	ASSERT_TRUE( listener->fin() );
}

TEST_F( InputTest, add_on_dispatch )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);
	Listener *listener = new Listener( _input );
	
	listener->setKeys(keys);
	ASSERT_TRUE( listener->init() );

	listener->onKeyAdd( new Listener( _input ) );

	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	ASSERT_TRUE( listener->callbacksCount() == 1 );
	
	ASSERT_TRUE( listener->fin() );
}

TEST_F( InputTest, remove_second_on_dispatch )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);
	
	Listener *listener1 = new Listener( _input );
	Listener *listener2 = new Listener( _input );

	listener1->setKeys(keys);
	listener2->setKeys(keys);
	ASSERT_TRUE( listener1->init() );
	ASSERT_TRUE( listener2->init() );

	listener1->onKeyDel( listener2 );

	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	ASSERT_TRUE( listener1->callbacksCount() == 1 );
	ASSERT_TRUE( listener2->callbacksCount() == 0 );
	
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	ASSERT_TRUE( listener1->callbacksCount() == 2 );
	ASSERT_TRUE( listener2->callbacksCount() == 0 );
	
	ASSERT_TRUE( listener1->fin() );
}

TEST_F( InputTest, remove_first_on_dispatch )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);

	Listener *listener1 = new Listener( _input );
	Listener *listener2 = new Listener( _input );
	
	listener1->setKeys(keys);
	listener2->setKeys(keys);
	ASSERT_TRUE( listener1->init() );
	ASSERT_TRUE( listener2->init() );

	listener2->onKeyDel( listener1 );

	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	ASSERT_TRUE( listener1->callbacksCount() == 1 );
	ASSERT_TRUE( listener2->callbacksCount() == 1 );
	
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	ASSERT_TRUE( listener1->callbacksCount() == 1 );
	ASSERT_TRUE( listener2->callbacksCount() == 2 );
	
	ASSERT_TRUE( listener2->fin() );
}

TEST_F( InputTest, remove_eachother_on_dispatch )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);

	Listener *listener1 = new Listener( _input );
	Listener *listener2 = new Listener( _input );

	listener1->setKeys(keys);
	listener2->setKeys(keys);
	ASSERT_TRUE( listener1->init() );
	ASSERT_TRUE( listener2->init() );

	listener1->onKeyDel( listener2 );
	listener2->onKeyDel( listener1 );

	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	ASSERT_TRUE( listener1->callbacksCount() == 1 );
	ASSERT_TRUE( listener2->callbacksCount() == 0 );
	
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	ASSERT_TRUE( listener1->callbacksCount() == 2 );
	ASSERT_TRUE( listener2->callbacksCount() == 0 );
	
	ASSERT_TRUE( listener1->fin() );
}

TEST_F( InputTest, remove_same_on_dispatch )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);
	
	Listener *listener1 = new Listener( _input );
	Listener *listener2 = new Listener( _input );
	Listener *listener3 = new Listener( _input );
	
	listener1->setKeys(keys);
	listener2->setKeys(keys);
	listener3->setKeys(keys);
	ASSERT_TRUE( listener1->init() );
	ASSERT_TRUE( listener2->init() );
	ASSERT_TRUE( listener3->init() );

	listener1->onKeyDel( listener3 );
	listener2->onKeyDel( listener3 );

	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	ASSERT_TRUE( listener1->callbacksCount() == 1 );
	ASSERT_TRUE( listener2->callbacksCount() == 1 );
	ASSERT_TRUE( listener3->callbacksCount() == 0 );
	
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	ASSERT_TRUE( listener1->callbacksCount() == 2 );
	ASSERT_TRUE( listener2->callbacksCount() == 2 );
	ASSERT_TRUE( listener3->callbacksCount() == 0 );
	
	ASSERT_TRUE( listener1->fin() );
	ASSERT_TRUE( listener2->fin() );
}

TEST_F( InputTest, add_two_on_dispatch )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);
	Listener *listener = new Listener( _input );

	listener->setKeys(keys);
	ASSERT_TRUE( listener->init() );

	listener->onKeyAdd( new Listener( _input ) );
	listener->onKeyDel( new Listener( _input ) );

	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	ASSERT_TRUE( listener->callbacksCount() == 1 );
	
	ASSERT_TRUE( listener->fin() );
}

TEST_F( InputTest, remove_two_on_dispatch )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);

	Listener *listener1 = new Listener( _input );
	Listener *listener2 = new Listener( _input );
	Listener *listener3 = new Listener( _input );

	listener1->setKeys(keys);
	listener2->setKeys(keys);
	listener3->setKeys(keys);
	ASSERT_TRUE( listener1->init() );
	ASSERT_TRUE( listener2->init() );
	ASSERT_TRUE( listener3->init() );

	listener1->onKeyDel( listener2 );
	listener1->onKeyDel( listener3 );
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );

	ASSERT_TRUE( listener1->callbacksCount() == 1 );
	
	ASSERT_TRUE( listener1->fin() );
}


TEST_F( InputTest, remove_self_on_dispatch )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);

	Listener *listener1 = new Listener( _input );
	
	listener1->setKeys(keys);
	ASSERT_TRUE( listener1->init() );

	listener1->onKeyDel( listener1 );
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );

	ASSERT_TRUE( listener1->callbacksCount() == 1 );
}

TEST_F( InputTest, remove_self_on_dispatch2 )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);

	Listener *listener1 = new Listener( _input );
	Listener *listener2 = new Listener( _input );
	
	listener1->setKeys(keys);
	listener2->setKeys(keys);
	ASSERT_TRUE( listener1->init() );
	ASSERT_TRUE( listener2->init() );

	listener1->onKeyDel( listener1 );
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );

	ASSERT_TRUE( listener1->callbacksCount() == 1 );
	
	ASSERT_TRUE( listener2->fin() );
}

TEST_F( InputTest, remove_self_on_dispatch3 )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);

	Listener *listener1 = new Listener( _input );
	Listener *listener2 = new Listener( _input );
	
	listener1->setKeys(keys);
	listener2->setKeys(keys);
	ASSERT_TRUE( listener1->init() );
	ASSERT_TRUE( listener2->init() );

	listener2->onKeyDel( listener2 );
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );

	ASSERT_TRUE( listener1->callbacksCount() == 1 );
	
	ASSERT_TRUE( listener1->fin() );
}

TEST_F( InputTest, remove_self_on_dispatch4 )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);

	Listener *listener1 = new Listener( _input );
	Listener *listener2 = new Listener( _input );
	Listener *listener3 = new Listener( _input );
	
	listener1->setKeys(keys);
	listener2->setKeys(keys);
	listener3->setKeys(keys);
	ASSERT_TRUE( listener1->init() );
	ASSERT_TRUE( listener2->init() );
	ASSERT_TRUE( listener3->init() );

	listener2->onKeyDel( listener2 );
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );

	ASSERT_TRUE( listener1->callbacksCount() == 1 );
	
	ASSERT_TRUE( listener1->fin() );
	ASSERT_TRUE( listener3->fin() );
}

TEST_F( InputTest, remove_and_add_on_dispatch )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);

	Listener *listener1 = new Listener( _input );
	Listener *listener2 = new Listener( _input );
	
	listener1->setKeys(keys);
	listener2->setKeys(keys);
	ASSERT_TRUE( listener1->init() );
	ASSERT_TRUE( listener2->init() );
	
	listener1->onKeyDel( listener2 );
	listener1->onKeyAdd( new Listener( _input ) );
	
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );

	ASSERT_TRUE( listener1->callbacksCount() == 1 );
	ASSERT_TRUE( listener2->callbacksCount() == 0 );
	
	ASSERT_TRUE( listener1->fin() );
}

TEST_F( InputTest, remove_and_add_same_on_dispatch )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);

	Listener *listener1 = new Listener( _input );
	Listener *listener2 = new Listener( _input );
	
	listener1->setKeys(keys);
	listener2->setKeys(keys);
	ASSERT_TRUE( listener1->init() );
	ASSERT_TRUE( listener2->init() );
	
	listener1->onKeyDel( listener2 );
	listener1->onKeyAdd( listener2 );
	
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );

	ASSERT_TRUE( listener1->callbacksCount() == 1 );
	ASSERT_TRUE( listener2->callbacksCount() == 1 );
	
	ASSERT_TRUE( listener1->fin() );
}

TEST_F( InputTest, remove_and_then_add_same_on_dispatch )
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);

	Listener *listener1 = new Listener( _input );
	Listener *listener2 = new Listener( _input );
	
	listener1->setKeys(keys);
	listener2->setKeys(keys);
	ASSERT_TRUE( listener1->init() );
	ASSERT_TRUE( listener2->init() );
	
	listener1->onKeyDel( listener2 );
	
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	ASSERT_TRUE( listener1->callbacksCount() == 1 );
	ASSERT_TRUE( listener2->callbacksCount() == 0 );

	listener1->onKeyAdd( listener2 );

	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	ASSERT_TRUE( listener1->callbacksCount() == 2 );
	ASSERT_TRUE( listener2->callbacksCount() == 0 );

	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );
	ASSERT_TRUE( listener1->callbacksCount() == 3 );
	ASSERT_TRUE( listener2->callbacksCount() == 1 );

	ASSERT_TRUE( listener1->fin() );
	ASSERT_TRUE( listener2->fin() );
}

TEST_F( InputTest, remove_listener_not_started)
{
	::util::key::Keys keys;
	keys.insert(::util::key::red);

	Listener *listener1 = new Listener( _input );
	Listener *listener2 = new Listener( _input );
	
	listener1->setKeys(keys);
	listener2->setKeys(keys);
	ASSERT_TRUE( listener1->init() );
	
	listener1->onKeyDel( listener2 );
	ASSERT_TRUE( _input->dispatchKey( ::util::key::red, true ) );

	ASSERT_TRUE( listener1->callbacksCount() == 1 );
	ASSERT_TRUE( listener2->callbacksCount() == 0 );

	ASSERT_TRUE( listener1->fin() );
}
