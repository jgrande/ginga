#include "imageplayer.h"
#include "../../util.h"
#include "../../../../src/player/imageplayer.h"
#include "../../../../src/device.h"

class ImagePlayerOpacity : public ImagePlayer {
protected:
    std::string property() const { return "opacity"; };
};

TEST_F( ImagePlayerOpacity, opaque ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );
 	ASSERT_TRUE ( _player->setProperty( "opacity", 1.0f ));
	ASSERT_TRUE ( _player->setProperty( "zIndex",2 ) );

  	player::Player* player2 = createPlayer( player::type::image );
  	ASSERT_TRUE ( player2->setProperty( "src", util::getImageName("image.png") ) );
  	ASSERT_TRUE ( player2->setProperty( "zIndex",1 ) );
  	ASSERT_TRUE ( player2->setProperty( "bounds", canvas::Rect(0,0,500,375) ) );

	ASSERT_TRUE( _player->play() );
  	ASSERT_TRUE( player2->play() );


	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "opaque" ) ) );

  	destroyPlayer( player2 );
}

TEST_F( ImagePlayerOpacity, default ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "zIndex",2 ) );

	player::Player* player2 = createPlayer( player::type::image );
	ASSERT_TRUE ( player2->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( player2->setProperty( "zIndex",1 ) );
	ASSERT_TRUE ( player2->setProperty( "bounds", canvas::Rect(0,0,500,375) ) );

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( player2->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "opaque" ) ) );

	destroyPlayer( player2 );
}

TEST_F( ImagePlayerOpacity, opacity_full_transparent ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "zIndex",2 ) );
	ASSERT_TRUE ( _player->setProperty( "opacity", 0.0f ));

	player::Player* player2 = createPlayer( player::type::image );
	ASSERT_TRUE ( player2->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( player2->setProperty( "zIndex",1 ) );
	ASSERT_TRUE ( player2->setProperty( "bounds", canvas::Rect(0,0,500,375) ) );

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( player2->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "full_transparent" ) ) );

	destroyPlayer( player2 );
}

TEST_F( ImagePlayerOpacity, opacity_half_transparent ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "zIndex",2 ) );
	ASSERT_TRUE ( _player->setProperty( "opacity", 0.5f ));

	player::Player* player2 = createPlayer( player::type::image );
	ASSERT_TRUE ( player2->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( player2->setProperty( "zIndex",1 ) );
	ASSERT_TRUE ( player2->setProperty( "bounds", canvas::Rect(0,0,500,375) ) );

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( player2->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "half_transparent" ) ) );

	destroyPlayer( player2 );
}

TEST_F( ImagePlayerOpacity, dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );
	ASSERT_TRUE ( _player->setProperty( "zIndex",2 ) );

	player::Player* player2 = createPlayer( player::type::image );
	ASSERT_TRUE ( player2->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( player2->setProperty( "zIndex",1 ) );
	ASSERT_TRUE ( player2->setProperty( "bounds", canvas::Rect(0,0,500,375) ) );

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( player2->play() );

	ASSERT_TRUE ( _player->setProperty( "opacity", 0.5f ));
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "half_transparent" ) ) );

	destroyPlayer( player2 );
}
