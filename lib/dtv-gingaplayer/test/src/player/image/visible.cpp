#include "imageplayer.h"
#include "../../util.h"
#include "../../../../src/player/imageplayer.h"

class ImagePlayerVisible : public ImagePlayer {
protected:
    std::string property() const { return "visible"; };
};

TEST_F( ImagePlayerVisible, player_visible ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "visible",true ) );
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(100,100,500,375) ));
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "player_visible" ) ) );
}

TEST_F( ImagePlayerVisible, player_invisible ) { // Same as visible_fill_default, but visible = false
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "visible",false ) );
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(100,100,500,375) ));
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "player_invisible" ) ) );
}

TEST_F( ImagePlayerVisible, player_visible_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(100,100,500,375) ));
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "visible",true ) );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "player_visible" ) ) );
}

TEST_F( ImagePlayerVisible, player_invisible_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(100,100,500,375) ));
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "visible",false ) );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "player_invisible" ) ) );
}
