#include "imageplayer.h"
#include "../../util.h"
#include "../../../../src/player/imageplayer.h"
#include "../../../../src/device.h"
#include "../../../../src/system.h"
#include <canvas/canvas.h>

class ImagePlayerLocation : public ImagePlayer {
protected:
    std::string property() const { return "location"; };
};

TEST_F( ImagePlayerLocation, top_left ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "top_left" ) ) );
}

TEST_F( ImagePlayerLocation, top_right ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds",canvas::Rect(620,0,100,100) ));
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "top_right" ) ) );
}

TEST_F( ImagePlayerLocation, bottom_left ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds",canvas::Rect(0,476,100,100) ));
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "bottom_left" ) ) );
}

TEST_F( ImagePlayerLocation, bottom_right ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds",canvas::Rect(620,476,100,100) ));
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "bottom_right" ) ) );
}

TEST_F( ImagePlayerLocation, middle ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds",canvas::Rect(310,238,100,100) ));
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "middle" ) ) );
}

TEST_F( ImagePlayerLocation, top_left_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds",canvas::Rect(310,238,100,100) ));
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "top_left" ) ) );
}

TEST_F( ImagePlayerLocation, top_right_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(620,0,100,100) ));
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "top_right" ) ) );
}

TEST_F( ImagePlayerLocation, bottom_left_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,476,100,100) ));
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "bottom_left" ) ) );
}

TEST_F( ImagePlayerLocation, bottom_right_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "bounds",canvas::Rect(620,476,100,100) ));
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "bottom_right" ) ) );
}

TEST_F( ImagePlayerLocation, middle_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "bounds",canvas::Rect(310,238,100,100) ));
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "middle" ) ) );
}

TEST_F( ImagePlayerLocation, three_players ) {
	canvas()->beginDraw();

	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds",canvas::Rect(0,0,360,288) ));
	ASSERT_TRUE( play( _player ) );

	player::Player* _player2 = createPlayer( player::type::image );
	ASSERT_TRUE ( _player2->setProperty( "src", util::getImageName("red_720_576.jpg") ) );
	ASSERT_TRUE ( _player2->setProperty( "bounds",canvas::Rect(0,288,360,288) ));
	ASSERT_TRUE( play( _player2 ) );

	player::Player* _player3 = createPlayer( player::type::image );
	ASSERT_TRUE ( _player3->setProperty( "src", util::getImageName("yellow.jpg") ) );
	ASSERT_TRUE ( _player3->setProperty( "bounds",canvas::Rect(360,0,360,288) ));
	ASSERT_TRUE( play( _player3 )  );

	canvas()->endDraw();

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "blue_red_yellow" ) ) );

	destroyPlayer( _player2 );
	destroyPlayer( _player3 );
}

