#include "htmlplayer.h"
#include "../../util.h"
#include "../../../../src/player/htmlplayer.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

std::string HTMLPlayer::playerType() const {
    return "HTMLPlayer";
}

std::string HTMLPlayer::property() const {
    return "basic";
}

player::type::type HTMLPlayer::type() const {
    return player::type::html;
}

TEST_F( HTMLPlayer, invalid_file ) {
    ASSERT_FALSE ( _player->setProperty( "src", "hello.html" ) );
}

TEST_F( HTMLPlayer, set_src_file ) {
    ASSERT_TRUE( _player->setProperty( "src", util::getImageName("hello.html") ) );
}
