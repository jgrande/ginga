#include "imageplayer.h"
#include "../../util.h"
#include "../../../../src/player/imageplayer.h"
#include <canvas/rect.h>
#include <canvas/point.h>

std::string ImagePlayer::playerType() const {
    return "ImagePlayer";
}

std::string ImagePlayer::property() const {
    return "basic";
}

player::type::type ImagePlayer::type() const {
	return player::type::image;
}

TEST_F( ImagePlayer, basic ) {
    ASSERT_FALSE ( _player->isPlaying() );
    ASSERT_FALSE ( _player->isPaused() );

    ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,500,300) ) );
    ASSERT_TRUE ( _player->setProperty("src",util::getImageName("image.png")) );
    ASSERT_TRUE ( _player->play() );
    ASSERT_TRUE ( _player->isPlaying() );
    ASSERT_FALSE ( _player->isPaused() );

    _player->pause( true );
    ASSERT_TRUE ( _player->isPlaying() );
    ASSERT_TRUE ( _player->isPaused() );

    _player->pause( false );
    ASSERT_TRUE ( _player->isPlaying() );
    ASSERT_FALSE( _player->isPaused() );

    _player->stop();
    ASSERT_FALSE ( _player->isPlaying() );
    ASSERT_FALSE( _player->isPaused() );

    ASSERT_TRUE ( _player->play() );
    _player->pause( true );
    _player->stop();
    ASSERT_FALSE ( _player->isPlaying() );
    ASSERT_FALSE( _player->isPaused() );

    _player->pause( true );
    ASSERT_FALSE( _player->isPaused() );
}

TEST_F( ImagePlayer, play ) {
    ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,500,375) ) );
	_player->play();
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("play") ) );
}

TEST_F( ImagePlayer, image_name_with_accent_character ) {
    ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("imáge.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,500,375) ) );
	_player->play();
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("play") ) );
}

TEST_F( ImagePlayer, stop ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,500,375) ) );
	_player->play();
	_player->stop();
	ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("stopped") ) );
}

TEST_F( ImagePlayer, invalid_file ) {
	ASSERT_FALSE ( _player->setProperty( "src",util::getImageName("invalid.png" )) );
	ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,500,375) ) );
	ASSERT_FALSE( _player->play() );
}

TEST_F( ImagePlayer, play_after_stop ) {
    ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("image.png") ) );
    ASSERT_TRUE ( _player->setProperty( "bounds", canvas::Rect(0,0,500,375) ) );
    ASSERT_TRUE( _player->play() );
    ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("play") ) );

    _player->stop();
    ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("stopped") ) );

    ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,500, 375) ) );
    ASSERT_TRUE( _player->play() );
    ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("play") ) );
}

TEST_F( ImagePlayer, set_src_file ) {
    ASSERT_TRUE( _player->setProperty( "src", util::getImageName("image.png") ) );
}

TEST_F( ImagePlayer, set_src_http ) {
    ASSERT_TRUE( _player->setProperty( "src", "http://path/image.png" ) );
}

TEST_F( ImagePlayer, set_src_https ) {
    ASSERT_TRUE( _player->setProperty( "src", "https://path/image.png" ) );
}

TEST_F( ImagePlayer, set_src_rtsp ) {
    ASSERT_FALSE( _player->setProperty( "src", "rtsp://path/image.png" ) );
}

TEST_F( ImagePlayer, set_src_rtp ) {
    ASSERT_FALSE( _player->setProperty( "src", "rtp://path/image.png" ) );
}

TEST_F( ImagePlayer, set_src_mirror ) {
    ASSERT_FALSE( _player->setProperty( "src", "ncl-mirror://path/image.png" ) );
}

TEST_F( ImagePlayer, set_src_sbtvd ) {
    ASSERT_FALSE( _player->setProperty( "src", "sbtvd-ts://path/image.png" ) );
}

TEST_F( ImagePlayer, set_src_invalid_schema ) {
    ASSERT_FALSE( _player->setProperty( "src", "invalid://path/image.png" ) );
}
