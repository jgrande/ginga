#include "htmlplayer.h"
#include "../../util.h"
#include "../../../../src/player/htmlplayer.h"

class HTMLPlayerLocation : public HTMLPlayer {
protected:
    std::string property() const { return "location"; };
};

TEST_F( HTMLPlayerLocation, DISABLED_move_topleft_to_bottomright ) {
	ASSERT_TRUE( _player->setProperty( "src", util::getImageName("hello.html") ));
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(),  getExpectedPath("before_moving")) );
	
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(620,476,100,100) ));
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("after_moving") ) );
}

TEST_F( HTMLPlayerLocation, DISABLED_move_topleft_to_bottomright_out_of_bounds ) {
	ASSERT_TRUE( _player->setProperty( "src", util::getImageName("hello.html") ));
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(),  getExpectedPath("before_moving")) );
	
	ASSERT_FALSE ( _player->setProperty( "bounds", canvas::Rect(700,500,100,100) ));
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_moving") ) );
}

TEST_F( HTMLPlayerLocation, DISABLED_resize) {
	ASSERT_TRUE( _player->setProperty( "src", util::getImageName("hello.html") ));
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(),  getExpectedPath("before_moving")) );
	
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,200,200) ));
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("after_resizeing") ) );
}

TEST_F( HTMLPlayerLocation, DISABLED_resize_out_of_bounds) {
	ASSERT_TRUE( _player->setProperty( "src", util::getImageName("hello.html") ));
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(),  getExpectedPath("before_moving")) );
	
	ASSERT_FALSE ( _player->setProperty( "bounds", canvas::Rect(0,0,800,600) ));
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_moving") ) );
}

TEST_F( HTMLPlayerLocation, DISABLED_move_and_resize) {
	ASSERT_TRUE( _player->setProperty( "src", util::getImageName("hello.html") ));
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(),  getExpectedPath("before_moving")) );
	
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(520,376,200,200) ));
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("after_moving_and_resizeing") ) );
}

TEST_F( HTMLPlayerLocation, DISABLED_move_and_resize_out_of_bounds) {
	ASSERT_TRUE( _player->setProperty( "src", util::getImageName("hello.html") ));
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(),  getExpectedPath("before_moving")) );
	
	ASSERT_FALSE ( _player->setProperty( "bounds", canvas::Rect(520,376,300,300) ));
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_moving") ) );
}

