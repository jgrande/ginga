#include "soundplayer.h"
#include "../../util.h"
#include "../../../../src/player/soundplayer.h"

class SoundPlayerBassLevel : public SoundPlayer {
protected:
    std::string property() const { return "BassLevel"; };
};

TEST_F( SoundPlayerBassLevel, DISABLED_minimum_level) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "bassLevel", 0.0f) );
}

TEST_F( SoundPlayerBassLevel, DISABLED_almost_minimum_level) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "bassLevel", 0.1f) );
}


TEST_F( SoundPlayerBassLevel, DISABLED_over_minimum_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_FALSE ( _player->setProperty( "bassLevel", -0.5f) );
}

TEST_F( SoundPlayerBassLevel, DISABLED_medium_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "bassLevel", 0.5f) );
}

TEST_F( SoundPlayerBassLevel, DISABLED_max_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "bassLevel", 1.0f) );
}

TEST_F( SoundPlayerBassLevel, DISABLED_over_max_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_FALSE ( _player->setProperty( "bassLevel", 1.1f) );
}

TEST_F( SoundPlayerBassLevel, DISABLED_almost_max_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "bassLevel", 0.9f) );
}
