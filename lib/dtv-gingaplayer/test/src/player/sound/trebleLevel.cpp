#include "soundplayer.h"
#include "../../util.h"
#include "../../../../src/player/soundplayer.h"

class SoundPlayerTrebleLevel : public SoundPlayer {
protected:
    std::string property() const { return "TrebleLevel"; };
};

TEST_F( SoundPlayerTrebleLevel, DISABLED_minimum_level) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "trebleLevel", 0.0f) );
}

TEST_F( SoundPlayerTrebleLevel, DISABLED_almost_minimum_level) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "trebleLevel", 0.1f) );
}


TEST_F( SoundPlayerTrebleLevel, DISABLED_over_minimum_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_FALSE ( _player->setProperty( "trebleLevel", -0.5f) );
}

TEST_F( SoundPlayerTrebleLevel, DISABLED_medium_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "trebleLevel", 0.5f) );
}

TEST_F( SoundPlayerTrebleLevel, DISABLED_max_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "trebleLevel", 1.0f) );
}

TEST_F( SoundPlayerTrebleLevel, DISABLED_over_max_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_FALSE ( _player->setProperty( "trebleLevel", 1.1f) );
}

TEST_F( SoundPlayerTrebleLevel, DISABLED_almost_max_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "trebleLevel", 0.9f) );
}
