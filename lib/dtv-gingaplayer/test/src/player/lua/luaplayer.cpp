#include "../../util.h"
#include "luaplayer.h"
#include "../../../../src/player/luaplayer.h"
#include "../../../../src/device.h"
#include "../../../../src/player/settings.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

void LuaPlayer::SetUp( void ){
	player::settings::init();
	Player::SetUp();
}

void LuaPlayer::TearDown( void ){
	player::settings::fin();
	Player::TearDown();
}

std::string LuaPlayer::playerType() const {
    return "LuaPlayer";
}

std::string LuaPlayer::property() const {
    return "basic";
}

std::string LuaPlayer::getLuaPath( std::string folder, std::string file ) const {
    fs::path path( util::getTestRoot() );
    path /= "lua";
    path /= folder;
    path /= property();
    path /= file;

    return path.string();
}

player::type::type LuaPlayer::type() const {
	return player::type::lua;
}

TEST_F( LuaPlayer, basic ) {
    fs::path luapath( util::getTestRoot() );
    luapath /= "lua";
    luapath /= "canvas";
    luapath /= "new1.lua";

    ASSERT_TRUE( _player->setProperty( "src",  luapath.string() ) );
    ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,720, 576) ) );

    ASSERT_TRUE( _player->play() );
    ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("basic") ) );

    _player->stop();
    ASSERT_TRUE( util::compareImages( canvas(), "nothing" ) );
}

TEST_F( LuaPlayer, play_after_stop ) {
    fs::path luapath( util::getTestRoot() );
    luapath /= "lua";
    luapath /= "canvas";
    luapath /= "new1.lua";

    ASSERT_TRUE( _player->setProperty( "src",  luapath.string() ) );
    ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,720, 576) ) );

    ASSERT_TRUE( _player->play() );
    ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("basic") ) );

    _player->stop();
    ASSERT_TRUE( util::compareImages( canvas(), "nothing" ) );

    ASSERT_TRUE( _player->play() );
    ASSERT_TRUE( util::compareImages( canvas(), getExpectedPath("basic") ) );
}

TEST_F( LuaPlayer, set_src_file ) {
    fs::path script( util::getTestRoot() );
    script /= "lua";
    script /= "canvas";
    script /= "new1.lua";

    ASSERT_TRUE( _player->setProperty( "src", script.string() ) );
}

TEST_F( LuaPlayer, set_src_http ) {
    ASSERT_TRUE( _player->setProperty( "src", "http://path/script.lua") );
}

TEST_F( LuaPlayer, set_src_https ) {
    ASSERT_TRUE( _player->setProperty( "src", "https://path/script.lua") );
}

TEST_F( LuaPlayer, set_src_rtsp ) {
    ASSERT_FALSE( _player->setProperty( "src", "rtsp://path/script.lua") );
}

TEST_F( LuaPlayer, set_src_rtp ) {
    ASSERT_FALSE( _player->setProperty( "src", "rtp://path/script.lua") );
}

TEST_F( LuaPlayer, set_src_mirror ) {
    ASSERT_FALSE( _player->setProperty( "src", "ncl-mirror://path/script.lua") );
}

TEST_F( LuaPlayer, set_src_sbtvd ) {
    ASSERT_FALSE( _player->setProperty( "src", "sbtvd-ts://path/script.lua") );
}

TEST_F( LuaPlayer, set_src_invalid_schema ) {
    ASSERT_FALSE( _player->setProperty( "src", "invalid://path/script.lua" ) );
}
