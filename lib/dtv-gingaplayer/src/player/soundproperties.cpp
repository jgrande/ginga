#include "soundproperties.h"
#include "../property/propertyimpl.h"
#include "../player.h"
#include <canvas/mediaplayer.h>
#include <util/log.h>
#include <boost/bind.hpp>

namespace player {

SoundProperties::SoundProperties( canvas::MediaPlayer *media )
	: _media( media )
{
	assert(_media);
	
	_soundLevel = 1.0f;
	_balanceLevel = 1.0f;
	_trebleLevel = 1.0f;
	_bassLevel = 1.0f;
}

SoundProperties::~SoundProperties()
{
}

void SoundProperties::registerProperties( Player *player ) {
	{	//	Add soundLevel
		PropertyImpl<float> *prop = new PropertyImpl<float>( false, _soundLevel );
		prop->setCheck( boost::bind( &check::range<float>, _1, 0.0f, 1.0f ) );
		prop->setApply( boost::bind( &SoundProperties::applySoundLevel, this ) );
		player->addProperty( property::type::soundLevel, prop );
	}

	// {	//	Add balanceLevel
	// 	PropertyImpl<float> *prop = new PropertyImpl<float>( false, _balanceLevel );
	// 	prop->setCheck( boost::bind( &check::range<float>, _1, 0.0f, 1.0f ) );
	// 	prop->setApply( boost::bind( &SoundProperties::applyBalanceLevel, this ) );		
	// 	player->addProperty( property::type::balanceLevel, prop );
	// }

	// {	//	Add trebleLevel
	// 	PropertyImpl<float> *prop = new PropertyImpl<float>( false, _trebleLevel );
	// 	prop->setCheck( boost::bind( &check::range<float>, _1, 0.0f, 1.0f ) );
	// 	prop->setApply( boost::bind( &SoundProperties::applyTrebleLevel, this ) );				
	// 	player->addProperty( property::type::trebleLevel, prop );
	// }

	// {	//	Add bassLevel
	// 	PropertyImpl<float> *prop = new PropertyImpl<float>( false, _bassLevel );
	// 	prop->setCheck( boost::bind( &check::range<float>, _1, 0.0f, 1.0f ) );
	// 	prop->setApply( boost::bind( &SoundProperties::applyBassLevel, this ) );						
	// 	player->addProperty( property::type::bassLevel, prop );
	// }
}

void SoundProperties::applySoundLevel() {
	LDEBUG("SoundProperties", "apply sound level, value=%f", _soundLevel);
	//_media->volume( _soundLevel );
}

void SoundProperties::applyBalanceLevel() {
	LDEBUG("SoundProperties", "apply balance level, value=%f", _balanceLevel );	
}

void SoundProperties::applyTrebleLevel() {
	LDEBUG("SoundProperties", "apply trebe Level, value=%f", _trebleLevel);	
}

void SoundProperties::applyBassLevel() {
	LDEBUG("SoundProperties", "apply bass level, value=%f", _bassLevel);	
}

}
