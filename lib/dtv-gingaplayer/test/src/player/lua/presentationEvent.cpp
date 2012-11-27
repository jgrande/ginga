#include "luaplayer.h"
#include "../../util.h"
#include "../../../../src/player/luaplayer.h"
#include <boost/filesystem.hpp>
#include <string>

namespace fs = boost::filesystem;

class LuaPlayerPresentationEvent : public LuaPlayer {
protected:
    std::string property() const { return "presentation"; };
};

TEST_F( LuaPlayerPresentationEvent, basic ){

    ASSERT_TRUE( _player->setProperty( "src",  getLuaPath("event", "basic.lua") ) );
    ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,720, 576) ) );

    ASSERT_TRUE( _player->play() );

    ASSERT_TRUE( _player->setProperty( "presentationEvent", "basic" ) );

    ASSERT_TRUE( util::compareImages( canvas(), "green" ) );

    _player->stop();
}

TEST_F( LuaPlayerPresentationEvent, before_play ){

    ASSERT_TRUE( _player->setProperty( "src",  getLuaPath("event", "basic.lua") ) );
    ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,720, 576) ) );
    ASSERT_FALSE( _player->setProperty( "presentationEvent", "basic" ) );
}

TEST_F( LuaPlayerPresentationEvent, after_stop ){

    ASSERT_TRUE( _player->setProperty( "src",  getLuaPath("event", "basic.lua") ) );
    ASSERT_TRUE( _player->setProperty( "bounds", canvas::Rect(0,0,720, 576) ) );

    ASSERT_TRUE( _player->play() );
    _player->stop();

    ASSERT_FALSE( _player->setProperty( "presentationEvent", "basic" ) );
}
