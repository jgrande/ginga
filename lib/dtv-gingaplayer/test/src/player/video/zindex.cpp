#include "videoplayer.h"
#include "../../util.h"
#include "../../../../src/player/videoplayer.h"

class VideoPlayerZIndex : public VideoPlayer {
protected:
    std::string property() const { return "zindex"; };
};

TEST_F( VideoPlayerZIndex, video_overlayed ) {
	ASSERT_TRUE( _player->setProperty( "src", util::getImageName("video.mp4") ));
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,100,100) ));

	player::Player* imgPlayer1 = createPlayer( player::type::image );
	ASSERT_TRUE ( imgPlayer1->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( imgPlayer1->setProperty( "bounds", canvas::Rect(0,0,720,576) ) );
	ASSERT_TRUE ( imgPlayer1->setProperty( "fit","fill" ) );
	ASSERT_TRUE ( imgPlayer1->setProperty( "zIndex", 0 ) );
	ASSERT_TRUE ( imgPlayer1->play() );

	player::Player* imgPlayer2 = createPlayer( player::type::image );
	ASSERT_TRUE ( imgPlayer2->setProperty( "src", util::getImageName("red_100_100.jpg") ) );
	ASSERT_TRUE ( imgPlayer2->setProperty( "bounds", canvas::Rect(0,0,360,288) ) );
	ASSERT_TRUE ( imgPlayer2->setProperty( "fit","fill" ) );
	ASSERT_TRUE ( imgPlayer2->setProperty( "zIndex", 1 ) );
	ASSERT_TRUE ( imgPlayer2->play() );

	player::Player* imgPlayer3 = createPlayer( player::type::image );
	ASSERT_TRUE ( imgPlayer3->setProperty( "src", util::getImageName("green.jpg") ) );
	ASSERT_TRUE ( imgPlayer3->setProperty( "bounds", canvas::Rect(360,288,360,288) ) );
	ASSERT_TRUE ( imgPlayer3->setProperty( "fit","fill" ) );
	ASSERT_TRUE ( imgPlayer3->setProperty( "zIndex", 3 ) );
	ASSERT_TRUE ( imgPlayer3->play() );

	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(240,192,240,192) ) );
	ASSERT_TRUE ( _player->setProperty( "zIndex", 2 ) );
	ASSERT_TRUE ( _player->play() );
	ASSERT_TRUE ( util::compareImages( canvas(),  getExpectedPath("video_overlayed")) );

	destroyPlayer( imgPlayer1 );
	destroyPlayer( imgPlayer2 );
	destroyPlayer( imgPlayer3 );
}
