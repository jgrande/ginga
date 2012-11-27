#pragma once

#include "../../player.h"

namespace player {
	class ImagePlayer;
}

class ImagePlayer : public Player {
protected:
	virtual std::string playerType() const;
	virtual std::string property() const;
	virtual player::type::type type() const;
};

