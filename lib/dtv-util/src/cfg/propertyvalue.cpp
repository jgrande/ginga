#include "propertyvalue.h"

#include <string>

namespace util {
namespace cfg {


PropertyValue::PropertyValue( const std::string &name, const char *def, const std::string &desc )
	: _name( name ), _default(std::string(def)), _value(std::string(def)), _description(desc) {
	init<std::string>();
}

PropertyValue::~PropertyValue( void ) {
	delete _validator;
}

const std::string &PropertyValue::name() const {
	return _name;
}

const std::string &PropertyValue::description() const {
	return _description;
}

bool PropertyValue::isModified() const {
	return ( *_isModified )( this );
}
const std::type_info &PropertyValue::type() const {
	return _value.type();
}
const std::string PropertyValue::asString() const {
	return ( *_asString )( this );
}
const std::string PropertyValue::asStringDefault() const {
	return ( *_asStringDefault )( this );
}

void PropertyValue::setStr( const std::string &val ) {
	( *_setString )( this, val.c_str() );
}

void PropertyValue::setStr( const char *val ) {
	( *_setString )( this, val );
}

void PropertyValue::makeVisible() {
	_visible = true;
}
void PropertyValue::makeInvisible() {
	_visible = false;
}
bool PropertyValue::isVisible() const {
	return _visible;
}

void PropertyValue::reset() {
	_value = _default;
}

void PropertyValue::onChange( const Callback &callback ) {
	_onChange = callback;
}

void PropertyValue::sendCallback() {
	if (!_onChange.empty()) {
		_onChange( _name );
	}
}

}
}
