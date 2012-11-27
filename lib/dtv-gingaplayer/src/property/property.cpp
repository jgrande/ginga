#include "property.h"
#include <canvas/canvas.h>
#include <canvas/color.h>
#include <canvas/system.h>
#include <boost/filesystem.hpp>

namespace player {

namespace fs = boost::filesystem;

namespace check {

bool color( const std::string &color ) {
	canvas::Color tmp;
	return canvas::color::get( color.c_str(), tmp );
}

bool fileExists( const std::string &file ) {
	return fs::exists( file );
}

bool position( canvas::Canvas *canvas, const canvas::Point &point ) {
	const canvas::Size &max = canvas->size();
	return point.x <= max.w && point.x >= 0 && point.y <= max.h && point.y >= 0;
}

bool size( canvas::Canvas *canvas, const canvas::Size &size ) {
	const canvas::Size &max = canvas->size();	
	return size.w <= max.w && size.w > 0 && size.h <= max.h && size.h > 0;
}

bool bounds( canvas::Canvas *canvas, const canvas::Rect &rect ) {
	const canvas::Size &max = canvas->size();	
	return rect.x+rect.w <= max.w && rect.w > 0 && rect.y+rect.h <= max.h && rect.h > 0;
}
	
}

Property::Property()
	: _changed( true )
{
}

Property::~Property() {
}

bool Property::assign( const bool &/*value*/ ) {
	throw std::runtime_error( "Invalid cast" );
}

bool Property::assign( const int &/*value*/ ) {
	throw std::runtime_error( "Invalid cast" );	
}

bool Property::assign( const float &/*value*/ ) {
	throw std::runtime_error( "Invalid cast" );	
}

bool Property::assign( const std::string &/*value*/ ) {
	throw std::runtime_error( "Invalid cast" );	
}

bool Property::assign( const char *value ) {
	if (!value) {
		return false;
	}
	return assign( std::string(value) );
}

bool Property::assign( const canvas::Size &/*value*/ ) {
	throw std::runtime_error( "Invalid cast" );	
}

bool Property::assign( const canvas::Point &/*value*/ ) {
	throw std::runtime_error( "Invalid cast" );	
}

bool Property::assign( const canvas::Rect &/*value*/ ) {
	throw std::runtime_error( "Invalid cast" );		
}

bool Property::assign( const std::pair<std::string,std::string> &/*value*/ ) {
	throw std::runtime_error( "Invalid cast" );
}

bool Property::assign( const std::pair<util::key::type,bool> &/*value*/ ) {
	throw std::runtime_error( "Invalid cast" );
}

void Property::markModified() {
	_changed = true;
}

bool Property::needRefresh() const {
	return false;
}

bool Property::canStart() const {
	return true;
}

bool Property::apply() {
	if (_changed) {
		applyChanges();
		_changed=false;
		return needRefresh();
	}
	return false;
}

void Property::applyChanges() {
}

bool Property::changed() const {
	return _changed;
}

}
