#include "../player.h"
#include "../../../src/player/timelinetimer.h"
#include "../../../src/system.h"
#include <canvas/system.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp> 

class TimeLineTimerTest : public Player {
public:
	TimeLineTimerTest() {}
	virtual ~TimeLineTimerTest() {}

protected:
	virtual void SetUp( void ) {
		Player::SetUp();
		_timer = createTimeLineTimer();
	}
	
	virtual void TearDown( void ) {
		delete _timer;
		Player::TearDown();
	}

	std::string playerType() const {
	    return "ImagePlayer";
	}

	std::string property() const {
	    return "basic";
	}

	player::type::type type() const {
		return player::type::image;
	}

	player::TimeLineTimer *_timer;
};

namespace impl {

boost::condition_variable wakeup;
boost::mutex mutex;

void wait() {
	boost::unique_lock<boost::mutex> lock( mutex );
	wakeup.wait(lock);
}

}

static void onExpired( int *value ) {
	(*value)++;
	impl::wakeup.notify_one();
}

TEST_F( TimeLineTimerTest, basic ) {
	ASSERT_TRUE( _timer->uptime() == 0 );
}

TEST_F( TimeLineTimerTest, start_stop_without_timers ) {
	ASSERT_TRUE( _timer->uptime() == 0 );
	_timer->start();
	boost::this_thread::sleep( boost::posix_time::milliseconds(10) );		
	ASSERT_TRUE( _timer->uptime() != 0 );
	_timer->stop();
	ASSERT_TRUE( _timer->uptime() == 0 );
}

TEST_F( TimeLineTimerTest, add_timer_before_start ) {
	int value=0;
	_timer->addTimer( 10, boost::bind(&onExpired,&value) );
	_timer->start();
	impl::wait();
	_timer->stop();
	ASSERT_TRUE( value == 1 );
}

TEST_F( TimeLineTimerTest, add_timer_after_start ) {
	int value=0;
	_timer->start();
	_timer->addTimer( 10, boost::bind(&onExpired,&value) );
	impl::wait();
	_timer->stop();
	ASSERT_TRUE( value == 1 );
}

TEST_F( TimeLineTimerTest, pause_basic ) {
	int value=0;
	_timer->addTimer( 10, boost::bind(&onExpired,&value) );
	ASSERT_TRUE( _timer->uptime() == 0 );

	_timer->start();
	impl::wait();
	ASSERT_TRUE( value == 1 );

	_timer->pause();
	util::DWORD up = _timer->uptime();
	boost::this_thread::sleep( boost::posix_time::milliseconds(20) );
	ASSERT_TRUE( _timer->uptime() == up );

	_timer->unpause();
	boost::this_thread::sleep( boost::posix_time::milliseconds(20) );
	ASSERT_TRUE( _timer->uptime() > up );
	
	_timer->stop();
}

static void onExpired2( int *value, std::vector<int> *values, int ms ) {
	//printf( "expired: value=%d, values[%d], ms=%d\n",
		// *value, values->size(), ms );
	(*value)++;
	values->push_back( ms );
	impl::wakeup.notify_one();	
}

TEST_F( TimeLineTimerTest, two_timers ) {
	int value=0;
	std::vector<int> values;

	_timer->addTimer( 10, boost::bind(&onExpired2,&value,&values,10) );	
	_timer->addTimer( 15, boost::bind(&onExpired2,&value,&values,15) );
	_timer->start();
	impl::wait();
	impl::wait();	
	_timer->stop();
	ASSERT_TRUE( value == 2 );
	ASSERT_TRUE( values.size() == 2 );	
	ASSERT_TRUE( values[0] == 10 );
	ASSERT_TRUE( values[1] == 15 );	
}

TEST_F( TimeLineTimerTest, stop_clean_timers ) {
	int value=0;
	_timer->addTimer( 10, boost::bind(&onExpired,&value) );	
	_timer->addTimer( 15, boost::bind(&onExpired,&value) );

	_timer->start();
	_timer->stop();
	ASSERT_TRUE( value == 0 );

	_timer->start();
	boost::this_thread::sleep( boost::posix_time::milliseconds(20) );
	_timer->stop();
	ASSERT_TRUE( value == 0 );
}

static void onExpired3( int *value, player::TimeLineTimer *timer ) {
	//printf( "expired: value=%d, values[%d], ms=%d\n",
	// *value, values->size(), ms );
	(*value)++;
	timer->addTimer( 10, boost::bind(&onExpired,value) );
}

TEST_F( TimeLineTimerTest, register_on_callback ) {
	int value=0;
	_timer->addTimer( 10, boost::bind(&onExpired3,&value,_timer) );

	_timer->start();
	boost::this_thread::sleep( boost::posix_time::milliseconds(50) );
	_timer->stop();
	ASSERT_TRUE( value == 2 );
}
