#pragma once

#include "graphicplayer.h"

namespace player {

class TextPlayer: public GraphicPlayer {
public:
	TextPlayer( Device *dev );
	virtual ~TextPlayer();

protected:
	virtual void refresh();
	virtual void registerProperties();

	bool readFile( std::string &text );
	void applyFont();
	void applyColor();

private:
	bool _applied;
	int _size;
	std::string _family;
	std::string _style;
	std::string _variant;
	std::string _weight;
	std::string _color;
};

}
