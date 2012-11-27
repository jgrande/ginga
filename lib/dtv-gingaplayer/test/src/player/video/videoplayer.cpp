#include "videoplayer.h"
#include "../../util.h"
#include "../../../../src/player/videoplayer.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

std::string VideoPlayer::playerType() const {
    return "VideoPlayer";
}

std::string VideoPlayer::property() const {
    return "basic";
}

player::type::type VideoPlayer::type() const {
    return player::type::video;
}

TEST_F( VideoPlayer, invalid_file ) {
    ASSERT_FALSE ( _player->setProperty( "src", "video.mp4" ) );
}

TEST_F( VideoPlayer, set_src_file ) {
    ASSERT_TRUE( _player->setProperty( "src", util::getImageName("video.mp4") ) );
}

TEST_F( VideoPlayer, set_src_http ) {
    ASSERT_FALSE( _player->setProperty( "src", "http://path/video.mp4") );
    ASSERT_FALSE( _player->setProperty( "src", "HTTP://path/video.mp4") );
    ASSERT_FALSE( _player->setProperty( "src", "hTtP://path/video.mp4") );
}

TEST_F( VideoPlayer, set_src_https ) {
    ASSERT_FALSE( _player->setProperty( "src", "https://path/video.mp4") );
    ASSERT_FALSE( _player->setProperty( "src", "HTTPS://path/video.mp4") );
    ASSERT_FALSE( _player->setProperty( "src", "hTtPs://path/video.mp4") );
}

TEST_F( VideoPlayer, set_src_rtsp ) {
    ASSERT_TRUE( _player->setProperty( "src", "rtsp://path/video.mp4") );
}

TEST_F( VideoPlayer, set_src_rtp ) {
    ASSERT_TRUE( _player->setProperty( "src", "rtp://path/video.mp4") );
}

TEST_F( VideoPlayer, set_src_mirror ) {
    ASSERT_FALSE( _player->setProperty( "src", "ncl-mirror://path/video.mp4") );
}

TEST_F( VideoPlayer, set_src_sbtvd ) {
    ASSERT_TRUE( _player->setProperty( "src", "sbtvd-ts://path/video.mp4") );
}

TEST_F( VideoPlayer, set_src_invalid_schema ) {
    ASSERT_FALSE( _player->setProperty( "src", "invalid://path/video.mp4" ) );
}
