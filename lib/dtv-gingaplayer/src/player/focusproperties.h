#pragma once

#include "surfaceproperties.h"

namespace player {

class FocusProperties : public SurfaceProperties {
public:
	FocusProperties( canvas::Canvas *canvas );
	virtual ~FocusProperties();
	
	virtual void registerProperties( Player *player );

protected:
	void refresh();
	void drawFocus();
	void drawSelected();
	void drawBorder( const std::string &strColor );
	void composeSurface( const std::string &src );

	virtual void calculateBounds( canvas::Rect &rect );
	virtual void getZIndex( int &zIndex );
	
private:
	bool _applied;
	bool _focus;
	bool _selected;
	std::string _borderColor;
	std::string _selBorderColor;
	int _width;
	float _transparency;
	std::string _focusSource;
	std::string _focusSelSource;
};

}

