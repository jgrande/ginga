#include "imageplayer.h"
#include "../../util.h"
#include "../../../../src/player/imageplayer.h"
#include "../../../../src/device.h"

class ImagePlayerZindex: public ImagePlayer {
protected:
    std::string property() const { return "zindex"; };
};

TEST_F( ImagePlayerZindex, 2_invalid_value ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	ASSERT_FALSE ( _player->setProperty( "zIndex",-1 ) );
}

TEST_F( ImagePlayerZindex, 2_superpuestos ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "zIndex",1 ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	
	player::Player* player2 = createPlayer( player::type::image );
	ASSERT_TRUE ( player2->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( player2->setProperty( "zIndex",2 ) );
	ASSERT_TRUE ( player2->setProperty( "bounds", canvas::Rect(150,150,100,100) ) );

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( player2->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "2_superpuestos" ) ) );

	destroyPlayer(player2);
}

TEST_F( ImagePlayerZindex, 3_superpuestos ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "zIndex",0 ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	
	player::Player* player2 = createPlayer( player::type::image );
	ASSERT_TRUE ( player2->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( player2->setProperty( "zIndex",2 ) );
	ASSERT_TRUE ( player2->setProperty( "bounds", canvas::Rect(150,150,100,100) ) );

	player::Player* player3 = createPlayer( player::type::image );
	ASSERT_TRUE ( player3->setProperty( "src", util::getImageName("green.jpg") ) );
	ASSERT_TRUE ( player3->setProperty( "zIndex",1 ) );
	ASSERT_TRUE ( player3->setProperty( "bounds", canvas::Rect(175,115,100,100) ) );

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( player2->play() );
	ASSERT_TRUE( player3->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "3_superpuestos" ) ) );

	destroyPlayer(player2);
	destroyPlayer(player3);
}

TEST_F( ImagePlayerZindex, 2_superpuestos_dinamico ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	
	player::Player* player2 = createPlayer( player::type::image );
	ASSERT_TRUE ( player2->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( player2->setProperty( "bounds", canvas::Rect(150,150,100,100) ) );

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( player2->play() );

	ASSERT_TRUE ( _player->setProperty( "zIndex",1 ) );
	ASSERT_TRUE ( player2->setProperty( "zIndex",2 ) );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "2_superpuestos" ) ) );

	destroyPlayer(player2);
}

TEST_F( ImagePlayerZindex, 3_superpuestos_dinamico ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	
	player::Player* player2 = createPlayer( player::type::image );
	ASSERT_TRUE ( player2->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( player2->setProperty( "bounds", canvas::Rect(150,150,100,100) ) );

	player::Player* player3 = createPlayer( player::type::image );
	ASSERT_TRUE ( player3->setProperty( "src", util::getImageName("green.jpg") ) );
	ASSERT_TRUE ( player3->setProperty( "bounds", canvas::Rect(175,115,100,100) ) );

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( player2->play() );
	ASSERT_TRUE( player3->play() );

	ASSERT_TRUE ( _player->setProperty( "zIndex",0 ) );
	ASSERT_TRUE ( player2->setProperty( "zIndex",2 ) );
	ASSERT_TRUE ( player3->setProperty( "zIndex",1 ) );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "3_superpuestos" ) ) );

	destroyPlayer(player2);
	destroyPlayer(player3);
}

TEST_F( ImagePlayerZindex, 2_superpuestos_swap ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "zIndex",1 ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(100,100,100,100) ) );
	
	player::Player* player2 = createPlayer( player::type::image );
	ASSERT_TRUE ( player2->setProperty( "src", util::getImageName("blue.jpg") ) );
	ASSERT_TRUE ( player2->setProperty( "zIndex",2 ) );
	ASSERT_TRUE ( player2->setProperty( "bounds", canvas::Rect(150,150,100,100) ) );

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( player2->play() );

	ASSERT_TRUE ( _player->setProperty( "zIndex",2 ) );
	ASSERT_TRUE ( player2->setProperty( "zIndex",1 ) );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "2_superpuestos_swap" ) ) );

	destroyPlayer(player2);
}
