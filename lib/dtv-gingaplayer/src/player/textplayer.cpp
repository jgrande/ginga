#include "textplayer.h"
#include "../property/propertyimpl.h"
#include <util/log.h>
#include <canvas/rect.h>
#include <canvas/color.h>
#include <canvas/font.h>
#include <canvas/surface.h>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>

namespace player {

static bool checkStyle( const std::string &style ) {
	return !strcmp( "normal", style.c_str() ) || !strcmp( "italic", style.c_str() );
}

static bool checkVariant( const std::string &variant ) {
	return !strcmp( "normal", variant.c_str() ) || !strcmp( "small-caps", variant.c_str() );
}

static bool checkWeight( const std::string &weight ) {
	return !strcmp( "normal", weight.c_str() ) || !strcmp( "bold", weight.c_str() );
}

static bool checkColor( const std::string &color ) {
	canvas::Color tmp;
	return canvas::color::get( color.c_str(), tmp );
}

TextPlayer::TextPlayer( Device *dev )
	: GraphicPlayer( dev )
{
	_applied = false;
	_size = -1;
	_family = "Tiresias";
	_color = "white";
	_style = "normal";
	_variant = "normal";
	_weight = "normal";
}

TextPlayer::~TextPlayer() {
}

void TextPlayer::refresh() {
	std::string text;
	if (readFile( text )) {
		int w = surface()->getBounds().w;
		int h = surface()->getBounds().h;
		surface()->drawText((canvas::Rect(0,0,w,h)), text );
	}
}

bool TextPlayer::readFile( std::string &text ) {
	std::ifstream ifs;
	std::string tmp;

	ifs.open( body().c_str() );
	if (!ifs.is_open()) {
		LERROR("TextPlayer", "failed to open file %s", body().c_str());
		return false;
	}
	while (!ifs.eof()) {
		getline( ifs, tmp );
		text += tmp + "\n";
	}
	ifs.close();
	return true;
}

void TextPlayer::registerProperties() {
	GraphicPlayer::registerProperties();
	
	{	//	Add fontSize
		MultiPropertyImpl<int> *prop = new MultiPropertyImpl<int>( _applied, true, _size );
		prop->setCheck( boost::bind( std::greater<int>(), _1, 0) );
		prop->setApply( boost::bind( &TextPlayer::applyFont, this) );
		addProperty( property::type::fontSize, prop );
	}
	{	//	Add fontFamily
		MultiPropertyImpl<std::string> *prop = new MultiPropertyImpl<std::string>( _applied, true, _family );
		prop->setCheck( boost::bind( &check::notEmpty, _1 ) );
		prop->setApply( boost::bind( &TextPlayer::applyFont,this) );
		addProperty( property::type::fontFamily, prop );
	}
	{	//	Add fontStyle
		MultiPropertyImpl<std::string> *prop = new MultiPropertyImpl<std::string>( _applied, true, _style );
		prop->setCheck( boost::bind( &checkStyle, _1 ) );
		prop->setApply( boost::bind( &TextPlayer::applyFont,this) );
		addProperty( property::type::fontStyle, prop );
	}
	{	//	Add fontVariant
		MultiPropertyImpl<std::string> *prop = new MultiPropertyImpl<std::string>( _applied, true, _variant );
		prop->setCheck( boost::bind( &checkVariant, _1 ) );
		prop->setApply( boost::bind( &TextPlayer::applyFont,this) );
		addProperty( property::type::fontVariant, prop );
	}
	{	//	Add fontWeight
		MultiPropertyImpl<std::string> *prop = new MultiPropertyImpl<std::string>( _applied, true, _weight );
		prop->setCheck( boost::bind( &checkWeight, _1 ) );
		prop->setApply( boost::bind( &TextPlayer::applyFont,this) );
		addProperty( property::type::fontWeight, prop );
	}
	{	//	Add fontColor
		PropertyImpl<std::string> *prop = new PropertyImpl<std::string>( true, _color );
		prop->setCheck( boost::bind( &checkColor, _1 ) );
		prop->setApply( boost::bind( &TextPlayer::applyColor,this) );
		addProperty( property::type::fontColor, prop );
	}
}

void TextPlayer::applyFont() {
	canvas::Font font;
	
	LINFO("TextPlayer", "Apply font: family=%s, style=%s, variant=%s, weight=%s, size=%d",
		_family.c_str(), _style.c_str(), _variant.c_str(), _weight.c_str(), _size);

	//	Apply size
	font.size( _size );

	//	Apply style
	font.italic( !strcmp( "italic", _style.c_str() ) );

	//	Apply variant
	font.smallCaps( !strcmp( "small-caps", _variant.c_str() ) );

	//	Apply weight
	font.bold( !strcmp( "bold", _weight.c_str() ) );
	
	{	//	Apply family
		std::vector<std::string> families;
		boost::erase_all(_family, " ");
		boost::split( families, _family, boost::is_any_of( "," ) );
		font.families(families);
		surface()->setFont(font);
	}
}

void TextPlayer::applyColor() {
	LINFO("TextPlayer", "Apply font color: color=%s", _color.c_str());
	canvas::Color c;
	canvas::color::get( _color.c_str(), c );
	surface()->setColor( c );
}

}

