#pragma once

#include "../../player.h"

namespace player {
	class LuaPlayer;
}

class LuaPlayer : public Player {

protected:
	virtual void SetUp( void );
	virtual void TearDown( void );

    virtual std::string playerType() const;
	virtual std::string property() const;
	std::string getLuaPath( std::string folder, std::string file ) const;
	virtual player::type::type type() const;
};
