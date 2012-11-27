#include "soundplayer.h"
#include "../../util.h"
#include "../../../../src/player/soundplayer.h"

class SoundPlayerBalanceLevel : public SoundPlayer {
protected:
    std::string property() const { return "BalanceLevel"; };
};

TEST_F( SoundPlayerBalanceLevel, DISABLED_minimum_level) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "balanceLevel", 0.0f) );
}

TEST_F( SoundPlayerBalanceLevel, DISABLED_almost_minimum_level) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "balanceLevel", 0.1f) );
}


TEST_F( SoundPlayerBalanceLevel, DISABLED_over_minimum_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_FALSE ( _player->setProperty( "balanceLevel", -0.5f) );
}

TEST_F( SoundPlayerBalanceLevel, DISABLED_medium_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "balanceLevel", 0.5f) );
}

TEST_F( SoundPlayerBalanceLevel, DISABLED_max_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "balanceLevel", 1.0f) );
}

TEST_F( SoundPlayerBalanceLevel, DISABLED_over_max_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_FALSE ( _player->setProperty( "balanceLevel", 1.1f) );
}

TEST_F( SoundPlayerBalanceLevel, DISABLED_almost_max_level ) {
	ASSERT_TRUE ( _player->setProperty( "src", util::getImageName("sound.ogg") ) );

	ASSERT_TRUE ( _player->setProperty( "balanceLevel", 0.9f) );
}
