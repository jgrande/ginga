#include "soundplayer.h"
#include "../../util.h"
#include "../../../../src/player/soundplayer.h"

class SoundPlayerSoundLevel : public SoundPlayer {
protected:
    std::string property() const { return "SoundLevel"; };
};

TEST_F( SoundPlayerSoundLevel, DISABLED_minimum_level) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "soundLevel", 0.0f) );
}

TEST_F( SoundPlayerSoundLevel, DISABLED_almost_minimum_level) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "soundLevel", 0.1f) );
}


TEST_F( SoundPlayerSoundLevel, DISABLED_over_minimum_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_FALSE ( _player->setProperty( "soundLevel", -0.5f) );
}

TEST_F( SoundPlayerSoundLevel, DISABLED_medium_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "soundLevel", 0.5f) );
}

TEST_F( SoundPlayerSoundLevel, DISABLED_max_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "soundLevel", 1.0f) );
}

TEST_F( SoundPlayerSoundLevel, DISABLED_over_max_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_FALSE ( _player->setProperty( "soundLevel", 1.1f) );
}

TEST_F( SoundPlayerSoundLevel, DISABLED_almost_max_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "soundLevel", 0.9f) );
}
