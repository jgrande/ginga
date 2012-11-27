#pragma once

#include "../../player.h"

class TextPlayer : public Player {
protected:
    virtual std::string playerType() const;
	virtual std::string property() const;
	virtual player::type::type type() const;
};
