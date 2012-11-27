#pragma once

#include "surfaceproperties.h"

namespace player {

class GraphicProperties : public SurfaceProperties {
public:
	GraphicProperties( canvas::Canvas *canvas );
	virtual ~GraphicProperties( void );

	void clear();
	virtual void registerProperties( Player *player );
	bool isVisible() const;

protected:
	//	Properties
	void applyOpacity();
	void applyVisible();

private:
	std::string _backgroundColor;
	float _opacity;
	bool _visible;
};

}
