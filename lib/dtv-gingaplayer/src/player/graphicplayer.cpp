#include "graphicplayer.h"
#include "graphicproperties.h"
#include "focusproperties.h"
#include "../property/propertyimpl.h"
#include "../device.h"
#include <util/log.h>
#include <canvas/system.h>
#include <canvas/point.h>
#include <canvas/size.h>
#include <canvas/canvas.h>
#include <canvas/surface.h>
#include <boost/bind.hpp>

namespace player {

static bool checkFit( const std::string &fitMode ) {
	if (fitMode == "fill" ||
		fitMode == "hidden" ||
		fitMode == "meet" ||
		fitMode == "meetBest" ||
		fitMode == "slice") {
		return true;
	}
	else {
		return false;
	}
}

GraphicPlayer::GraphicPlayer( Device *dev )
	: Player( dev ), _fitMode( "fill" )
{
	canvas::Canvas *canv = canvas();
	assert(canv);
	_graphic = new GraphicProperties( canv );
	_focus = new FocusProperties( canv );

	//	Register graphics properties events
	_graphic->onSizeChanged( boost::bind(&GraphicPlayer::onSizeChanged,this,_1) );
	_graphic->onPositionChanged( boost::bind(&GraphicPlayer::onPositionChanged,this,_1) );
}

GraphicPlayer::~GraphicPlayer()
{
	delete _graphic;
	delete _focus;
}

//	Initialization
bool GraphicPlayer::startPlay() {
	LDEBUG("GraphicPlayer", "Start play");
	if (!_graphic->createSurface()) {
		return false;
	}

	if (!_focus->createSurface()) {
		_graphic->destroy();
		return false;
	}
	
	return true;
}

void GraphicPlayer::stopPlay() {
	LDEBUG("GraphicPlayer", "Stop play");
	_graphic->destroy();
	_focus->destroy();
	canvas()->flush();
}

void GraphicPlayer::beginRefresh() {
	LDEBUG("GraphicPlayer", "Begin refresh");
	_graphic->clear();
}

void GraphicPlayer::onPropertyChanged() {
	LDEBUG("GraphicPlayer", "On property changed");
	surface()->flush();
}

void GraphicPlayer::registerProperties() {
	Player::registerProperties();
	_graphic->registerProperties(this);
	_focus->registerProperties(this);

	{	//	Property fit
		PropertyImpl<std::string> *fit = new PropertyImpl<std::string>(true,_fitMode);
		fit->setCheck( boost::bind(&checkFit,_1) );
		addProperty( property::type::fit, fit );
	}
}

//	Events
void GraphicPlayer::onSizeChanged( const canvas::Size & /*size*/ ) {
}

void GraphicPlayer::onPositionChanged( const canvas::Point & /*point*/ ) {
}

//	Getters
canvas::Canvas *GraphicPlayer::canvas() const {
	return device()->system()->canvas();
}

canvas::Surface *GraphicPlayer::surface() const {
	return _graphic->surface();
}

bool GraphicPlayer::isVisible() const {
	return _graphic->isVisible();
}

fit::mode::type GraphicPlayer::getFitMode() const {
	fit::mode::type mode;
	if (_fitMode == "hidden") {
		mode = fit::mode::hidden;		
	}
	else if (_fitMode == "meet") {
		mode = fit::mode::meet;				
	}
	else if (_fitMode == "meetBest") {
		mode = fit::mode::meetBest;				
	}
	else if (_fitMode == "slice") {
		mode = fit::mode::slice;						
	}
	else {
		mode = fit::mode::fill;
	}
	return mode;
}

}
