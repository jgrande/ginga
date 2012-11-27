#include "soundplayer.h"
#include "../../util.h"
#include "../../../../src/player/soundplayer.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

std::string SoundPlayer::playerType() const {
    return "SoundPlayer";
}

std::string SoundPlayer::property() const {
    return "basic";
}

player::type::type SoundPlayer::type() const {
	return player::type::audio;
}

TEST_F( SoundPlayer, DISABLED_basic ) {
    ASSERT_FALSE ( _player->isPlaying() );
    ASSERT_FALSE ( _player->isPaused() );

    ASSERT_TRUE ( _player->setProperty("src",util::getImageName("sound.ogg")) );
    
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

TEST_F( SoundPlayer, DISABLED_invalid_file ) {
	ASSERT_FALSE ( _player->setProperty( "src", "Invalid" ) );
}

TEST_F( SoundPlayer, DISABLED_set_src_file ) {
    ASSERT_TRUE( _player->setProperty( "src", util::getImageName("audio.mp3") ) );
}

TEST_F( SoundPlayer, DISABLED_set_src_http ) {
    ASSERT_TRUE( _player->setProperty( "src", "http://path/audio.mp3") );
}

TEST_F( SoundPlayer, DISABLED_set_src_https ) {
    ASSERT_TRUE( _player->setProperty( "src", "https://path/audio.mp3") );
}

TEST_F( SoundPlayer, DISABLED_set_src_rtsp ) {
    ASSERT_TRUE( _player->setProperty( "src", "rtsp://path/audio.mp3") );
}

TEST_F( SoundPlayer, DISABLED_set_src_rtp ) {
    ASSERT_TRUE( _player->setProperty( "src", "rtp://path/audio.mp3") );
}

TEST_F( SoundPlayer, DISABLED_set_src_mirror ) {
    ASSERT_TRUE( _player->setProperty( "src", "ncl-mirror://path/audio.mp3") );
}

TEST_F( SoundPlayer, DISABLED_set_src_sbtvd ) {
    ASSERT_TRUE( _player->setProperty( "src", "sbtvd-ts://path/audio.mp3") );
}

TEST_F( SoundPlayer, DISABLED_set_src_invalid_schema ) {
    ASSERT_FALSE( _player->setProperty( "src", "invalid://path/audio.mp3" ) );
}
