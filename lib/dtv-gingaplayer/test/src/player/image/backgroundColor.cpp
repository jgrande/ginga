#include "imageplayer.h"
#include "../../util.h"
#include "../../../../src/player/imageplayer.h"

class ImagePlayerBackgroundColor : public ImagePlayer {
protected:
    std::string property() const { return "backgroundColor"; };
};

TEST_F( ImagePlayerBackgroundColor, backgroundColor_white ){
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "white"));
	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("white") ) );

}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_black ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "black"));
	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("black") ) );

}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_silver ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "silver"));
	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("silver") ) );

}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_gray ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "gray"));
	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("gray") ) );

}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_red ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "red"));
	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("red") ) );

}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_maroon ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "maroon"));

	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("maroon") ) );
}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_fuchsia ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "fuchsia"));

	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("fuchsia") ) );
}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_purple ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "purple"));

	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("purple") ) );
}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_lime ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "lime"));

	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("lime") ) );
}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_green ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "green"));

	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("green") ) );
}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_yellow ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "yellow"));

	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("yellow") ) );
}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_olive ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "olive"));

	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("olive") ) );
}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_blue ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "blue"));

	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("blue") ) );
}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_navy ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "navy"));

	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("navy") ) );
}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_aqua ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "aqua"));

	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("aqua") ) );
}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_teal ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "teal"));

	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("teal") ) );
}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_transparent ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );
	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "transparent"));

	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("transparent") ) );
}

TEST_F( ImagePlayerBackgroundColor, backgroundColor_dynamic ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( _player->setProperty( "fit","hidden" ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(50,50,500,500) ) );

	ASSERT_TRUE( _player->play() );

	ASSERT_TRUE ( _player->setProperty( "backgroundColor", "white"));
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("white") ) );
}
