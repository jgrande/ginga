#include "graphicproperties.h"
#include "../property/propertyimpl.h"
#include "../player.h"
#include <util/log.h>
#include <canvas/system.h>
#include <canvas/canvas.h>
#include <canvas/surface.h>
#include <boost/bind.hpp>

namespace player {

GraphicProperties::GraphicProperties( canvas::Canvas *canvas )
	: SurfaceProperties( canvas )
{
	_opacity = 1.0f;
	_visible = true;
	_backgroundColor = "transparent";
}

GraphicProperties::~GraphicProperties( void )
{
}

void GraphicProperties::clear() {
	canvas::Surface *s = surface();

	//Get background color
	canvas::Color previousColor = s->getColor();

	canvas::Color backColor;
	canvas::color::get( _backgroundColor.c_str(), backColor );
	s->setColor(backColor);

	canvas::Rect rect = s->getBounds();
	rect.x = 0;
	rect.y = 0;
	s->setCompositionMode( canvas::composition::source );
	s->fillRect( rect );
	s->setCompositionMode( canvas::composition::source_over );

	s->setColor(previousColor);
}

void GraphicProperties::registerProperties( Player *player ) {
	SurfaceProperties::registerProperties( player );
	
	{	//	Add Opacity
		PropertyImpl<float> *prop=new PropertyImpl<float>( false, _opacity );
		prop->setCheck( boost::bind(&check::range<float>,_1,0.0f,1.0f) );
		prop->setApply( boost::bind(&GraphicProperties::applyOpacity,this) );
		player->addProperty( property::type::opacity, prop );
	}
	{	//	Add backgroundColor
		PropertyImpl<std::string> *prop=new PropertyImpl<std::string>( true, _backgroundColor );
		prop->setCheck( boost::bind(&check::color,_1) );
		player->addProperty( property::type::backgroundColor, prop );
	}
	{	//	Add visible
		PropertyImpl<bool> *prop=new PropertyImpl<bool>( false, _visible );
		prop->setApply( boost::bind(&GraphicProperties::applyVisible,this) );
		player->addProperty( property::type::visible, prop );
	}
}

bool GraphicProperties::isVisible() const {
	return _visible;
}

void GraphicProperties::applyOpacity() {
	LDEBUG("GraphicProperties", "apply opacity, value=%f", _opacity);
	surface()->setOpacity( (util::BYTE) (255 * _opacity) );
}

void GraphicProperties::applyVisible() {
	LDEBUG("GraphicProperties", "apply visible, value=%d", _visible );
	surface()->setVisible( _visible );
}

}
