#include "luaplayer.h"
#include "../../util.h"
#include "../../../../src/player/luaplayer.h"
#include "../../../../src/player/settings.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

std::string getPath( const std::string &file ) {
	fs::path luapath( util::getTestRoot() );
	luapath /= "lua";
	luapath /= "settings";
	luapath /= "update";
	luapath /= file;
	return luapath.string();
}

TEST_F( LuaPlayer, shared ) {
	ASSERT_TRUE( _player->setProperty( "src",  getPath("updateShared.lua") ) );
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0, 0, 720, 576) ) );

	player::settings::setProperty( "shared.myVar", "val", true );
	ASSERT_TRUE( _player->play() );
	player::settings::setProperty( "shared.myVar", "anotherVal");
	ASSERT_TRUE( _player->setProperty( "attributionEvent", std::make_pair<std::string, std::string>("basic","1") ) );

	ASSERT_TRUE( util::compareImages( canvas(), "green" ) );
}

TEST_F( LuaPlayer, service ) {
	ASSERT_TRUE( _player->setProperty( "src",  getPath("updateService.lua") ) );
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0, 0, 720, 576) ) );

	ASSERT_TRUE( _player->play() );
	player::settings::setProperty( "service.currentFocus", "1" );
	ASSERT_TRUE( _player->setProperty( "attributionEvent", std::make_pair<std::string, std::string>("basic","1") ) );

	ASSERT_TRUE( util::compareImages( canvas(), "green" ) );
}

TEST_F( LuaPlayer, defaults ) {
	ASSERT_TRUE( _player->setProperty( "src",  getPath("updateDefault.lua") ) );
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0, 0, 720, 576) ) );

	ASSERT_TRUE( _player->play() );
	player::settings::setProperty( "default.focusBorderColor", "green" );
	ASSERT_TRUE( _player->setProperty( "attributionEvent", std::make_pair<std::string, std::string>("basic","1") ) );

	ASSERT_TRUE( util::compareImages( canvas(), "green" ) );
}

TEST_F( LuaPlayer, channel ) {
	ASSERT_TRUE( _player->setProperty( "src",  getPath("updateChannel.lua") ) );
	ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0, 0, 720, 576) ) );

	ASSERT_TRUE( _player->play() );
	player::settings::setProperty( "channel.keyCapture", "4" );
	ASSERT_TRUE( _player->setProperty( "attributionEvent", std::make_pair<std::string, std::string>("basic","1") ) );

	ASSERT_TRUE( util::compareImages( canvas(), "green" ) );
}
