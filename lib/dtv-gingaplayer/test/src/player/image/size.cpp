#include "imageplayer.h"
#include "../../util.h"
#include "../../../../src/player/imageplayer.h"

class ImagePlayerSize : public ImagePlayer {
protected:
    std::string property() const { return "size"; };
};

TEST_F( ImagePlayerSize, 100px ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "100px" ) ) );
}

TEST_F( ImagePlayerSize, 100px_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_720_576.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,300,300) ) );	
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "100px" ) ) );
}

TEST_F( ImagePlayerSize, full ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_720_576.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,720,576) ) );
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "full" ) ) );
}

TEST_F( ImagePlayerSize, half ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_720_576.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,360,288) ) );
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "half" ) ) );
}

TEST_F( ImagePlayerSize, zero ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_720_576.jpg") ) );
	ASSERT_FALSE ( _player->setProperty( "bounds", canvas::Rect(0,0,0,0) ) );
}

TEST_F( ImagePlayerSize, full_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_720_576.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );	
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,720,576) ) );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "full" ) ) );
}

TEST_F( ImagePlayerSize, half_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_720_576.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );		
	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,360,288) ) );
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath( "half" ) ) );
}

TEST_F( ImagePlayerSize, zero_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ) );	
	_player->play();
	ASSERT_FALSE ( _player->setProperty( "bounds", canvas::Rect(0,0,0,0) ) );
}
