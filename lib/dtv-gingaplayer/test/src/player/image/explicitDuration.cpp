#include "imageplayer.h"
#include "../../util.h"
#include "../../../../src/player/imageplayer.h"
#include "../../../../src/system.h"
#include <canvas/system.h>
#include <boost/thread.hpp>

class ImagePlayerExplicitDuration : public ImagePlayer {
protected:
    std::string property() const { return "explicitDuration"; };
};

static void cb_wakeup( boost::condition_variable *wakeup) {
	wakeup->notify_one();
}

// Test setting explicitDur to 2ms and call a timer to check the image after that time
TEST_F( ImagePlayerExplicitDuration, duration_of_1ms ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "explicitDur", 1000 ) );


	ASSERT_TRUE ( _player->play() );

	// Assert that the player is initially playing
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_finish") ) );

	boost::condition_variable wakeup;
	boost::mutex mutex;
	boost::unique_lock<boost::mutex> lock( mutex );
	_player->onStopped( boost::bind(&cb_wakeup, &wakeup) );
	wakeup.wait(lock);

	// Assert that the player is not playing after 1000 ms
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("after_finish") ) );
}

// Tests setting explicitDur to 0
TEST_F( ImagePlayerExplicitDuration, duration_of_0ms ) {
    ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
    ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );
    ASSERT_TRUE ( _player->setProperty( "explicitDur", 0 ) );
    ASSERT_TRUE ( _player->play() );

    ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_finish") ) );
}

// Tests setting explicitDur to an invalid value
TEST_F( ImagePlayerExplicitDuration, set_negative_value ) {
    ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
    ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );
    ASSERT_FALSE( _player->setProperty( "explicitDur", -1 ) );
    ASSERT_TRUE ( _player->play() );
    ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_finish") ) );
}

// Test unsetting explicitDur
TEST_F( ImagePlayerExplicitDuration, unsetting_explicitDur ) {
    ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
    ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );
    ASSERT_TRUE ( _player->setProperty( "explicitDur", 100 ) );
    ASSERT_TRUE ( _player->play() );
    ASSERT_TRUE ( _player->setProperty( "explicitDur", 0 ) );

    ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_finish") ) );

    boost::condition_variable wakeup;
    boost::mutex mutex;
    boost::unique_lock<boost::mutex> lock( mutex );

    registerTimer(300, boost::bind(&cb_wakeup, &wakeup));
    wakeup.wait(lock);

    // Assert that the player is still playing after 1000 ms beacuse the explicitDur was unsetted
    ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_finish") ) );
}

// Test setting explicitDur dinamically with a time smaller than the uptime
TEST_F( ImagePlayerExplicitDuration, DISABLED_set_dinamically_lt_uptime ) {
    ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
    ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );

    ASSERT_TRUE ( _player->play() );

    ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_finish") ) );

    int uptime = _player->uptime();
    ASSERT_TRUE ( _player->setProperty( "explicitDur", uptime ) );

    ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("after_finish") ) );
}

// Test setting explicitDur dinamically with a time greater than the uptime
TEST_F( ImagePlayerExplicitDuration, set_dinamically_gt_uptime ) {
    ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
    ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );

    ASSERT_TRUE ( _player->play() );

    ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_finish") ) );

    int uptime = _player->uptime();
    ASSERT_TRUE ( _player->setProperty( "explicitDur", uptime + 500  ) );

    ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_finish") ) );

    boost::condition_variable wakeup;
    boost::mutex mutex;
    boost::unique_lock<boost::mutex> lock( mutex );
    _player->onStopped( boost::bind(&cb_wakeup, &wakeup) );
    wakeup.wait(lock);

    ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("after_finish") ) );
}

// Test setting explicitDur dinamically with a time greater than the uptime
TEST_F( ImagePlayerExplicitDuration, set_dinamically_not_enough_gt_uptime ) {
	boost::condition_variable wakeup;

	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );
	_player->onStopped( boost::bind(&cb_wakeup, &wakeup) );

	ASSERT_TRUE ( _player->play() );

	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_finish") ) );

	int uptime = _player->uptime();
	ASSERT_TRUE ( _player->setProperty( "explicitDur", uptime + 80  ) );

	boost::mutex mutex;
	boost::unique_lock<boost::mutex> lock( mutex );
	wakeup.wait(lock);

	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("after_finish") ) );
}
