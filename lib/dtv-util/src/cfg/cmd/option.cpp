#include "option.h"
#include "../cfg.h"
#include <string>

namespace util {
namespace cfg {
namespace cmd {

Option::Option( const std::string &path, const std::string &alias)
	: _path(path), _alias(alias), _sname("") {
	_showDef = true;
}

Option::~Option() {
}

const std::string &Option::property() const {
	return _path;
}

const std::string &Option::alias() const {
	return _alias;
}

const std::string Option::def() const {
	std::string val("");
	if (_showDef) {
		val = cfg::get().defaultAsString(_path);
	}
	return val;
}

char Option::sname() const {
	return _sname[0];
}

bool Option::hasShortName() const {
	return !_sname.empty();
}

const std::string &Option::snamestr() const {
	return _sname;
}

void Option::setsname( char sname ) {
	_sname = std::string(1,sname);
}

void Option::noShowDefault() {
	_showDef = false;
}

void Option::showDefault() {
	_showDef = true;
}

void Option::set( const std::string &str ) {
	if ( cfg::get().type(_path) == typeid( std::string ) || !str.empty()) {
		cfg::get().setStr(_path, str);
	} else if (str.empty()) {
		set();
	}
}

void Option::set() {
	if (cfg::get().type(_path) == typeid( bool )) {
		bool bval = cfg::getValue<bool> (_path);
		cfg::setValue(_path, !bval);
	}
}

const std::string Option::desc() {
	return cfg::get().desc(_path);
}

bool Option::exists() const {
	return cfg::get().existsValue(_path);
}

}
}
}
