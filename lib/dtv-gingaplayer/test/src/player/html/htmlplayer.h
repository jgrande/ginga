#pragma once

#include "../../player.h"

namespace player {
    class HTMLPlayer;
}

class HTMLPlayer : public Player {
protected:
    virtual std::string playerType() const;
    virtual std::string property() const;
    virtual player::type::type type() const;
};
