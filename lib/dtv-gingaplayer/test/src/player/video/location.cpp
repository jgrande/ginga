#include "videoplayer.h"
#include "../../util.h"
#include "../../../../src/player/videoplayer.h"

class VideoPlayerLocation : public VideoPlayer {
protected:
    std::string property() const { return "location"; };
};

namespace impl {

static void setBackgroundImg( player::Player *imgPlayer ) {
	ASSERT_TRUE ( imgPlayer->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( imgPlayer->setProperty( "bounds", canvas::Rect(0,0,720,576) ) );
	ASSERT_TRUE ( imgPlayer->setProperty( "fit","fill" ) );
	ASSERT_TRUE ( imgPlayer->setProperty( "zIndex", 0 ) );
	ASSERT_TRUE( imgPlayer->play() );
}

}

TEST_F( VideoPlayerLocation, move_topleft_to_bottomright ) {
	ASSERT_TRUE( _player->setProperty( "src", util::getImageName("video.mp4") ));
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));

	player::Player* imgPlayer = createPlayer( player::type::image );
	impl::setBackgroundImg(imgPlayer);

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(),  getExpectedPath("before_moving")) );
	
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(620,476,100,100) ));
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("after_moving") ) );

	destroyPlayer(imgPlayer);
}

TEST_F( VideoPlayerLocation, move_topleft_to_bottomright_out_of_bounds ) {
	ASSERT_TRUE( _player->setProperty( "src", util::getImageName("video.mp4") ));
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));

	player::Player* imgPlayer = createPlayer( player::type::image );
	impl::setBackgroundImg(imgPlayer);

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(),  getExpectedPath("before_moving")) );
	
	ASSERT_FALSE ( _player->setProperty( "bounds", canvas::Rect(700,500,100,100) ));
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_moving") ) );

	destroyPlayer(imgPlayer);
}

TEST_F( VideoPlayerLocation, resize) {
	ASSERT_TRUE( _player->setProperty( "src", util::getImageName("video.mp4") ));
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));

	player::Player* imgPlayer = createPlayer( player::type::image );
	impl::setBackgroundImg(imgPlayer);

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(),  getExpectedPath("before_moving")) );
	
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,200,200) ));
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("after_resizeing") ) );

	destroyPlayer(imgPlayer);
}

TEST_F( VideoPlayerLocation, resize_out_of_bounds) {
	ASSERT_TRUE( _player->setProperty( "src", util::getImageName("video.mp4") ));
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));

	player::Player* imgPlayer = createPlayer( player::type::image );
	impl::setBackgroundImg(imgPlayer);

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(),  getExpectedPath("before_moving")) );
	
	ASSERT_FALSE ( _player->setProperty( "bounds", canvas::Rect(0,0,800,600) ));
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_moving") ) );

	destroyPlayer(imgPlayer);
}

TEST_F( VideoPlayerLocation, move_and_resize) {
	ASSERT_TRUE( _player->setProperty( "src", util::getImageName("video.mp4") ));
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));

	player::Player* imgPlayer = createPlayer( player::type::image );
	impl::setBackgroundImg(imgPlayer);

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(),  getExpectedPath("before_moving")) );
	
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(520,376,200,200) ));
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("after_moving_and_resizeing") ) );

	destroyPlayer(imgPlayer);
}

TEST_F( VideoPlayerLocation, move_and_resize_out_of_bounds) {
	ASSERT_TRUE( _player->setProperty( "src", util::getImageName("video.mp4") ));
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));

	player::Player* imgPlayer = createPlayer( player::type::image );
	impl::setBackgroundImg(imgPlayer);

	ASSERT_TRUE( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(),  getExpectedPath("before_moving")) );
	
	ASSERT_FALSE ( _player->setProperty( "bounds", canvas::Rect(520,376,300,300) ));
	ASSERT_TRUE ( util::compareImages( canvas(), getExpectedPath("before_moving") ) );

	destroyPlayer(imgPlayer);
}
