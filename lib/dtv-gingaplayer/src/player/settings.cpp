#include "settings.h"
#include "lua/settings/settings.h"
#include <canvas/color.h>
#include <util/log.h>
#include <util/string.h>
#include <util/cfg/cfg.h>
#include <util/cfg/configregistrator.h>
#include <boost/algorithm/string.hpp>
#include <stdio.h>

REGISTER_INIT_CONFIG(system) {
	root().addNode( "system" )
			.addValue( "language", "", "es" )
			.addValue( "caption", "", "es" )
			.addValue( "subtitle", "", "es" )
			.addValue( "returnBitRate(0)", "", "" )
			.addValue( "screenSize", "", "(0, 0)" )
			.addValue( "screenGraphicSize", "", "(0, 0)" )
			.addValue( "audioType", "", "stereo" )
			.addValue( "screenSize(0)", "", "(0, 0)" )
			.addValue( "screenGraphicSize(0)", "", "(0, 0)" )
			.addValue( "audioType(0)", "", "stereo" )
			.addValue( "devNumber(0)", "", "1" )
			.addValue( "classType", "", "active" )
			.addValue( "info(0)", "", "" )
			.addValue( "classNumber", "", "1" )
			.addValue( "CPU", "", "" )
			.addValue( "memory", "", "" )
			.addValue( "operatingSystem", "", "" )
			.addValue( "luaVersion", "", "5.1" );

	util::cfg::get("system").addNode("ncl").addValue( "version", "", "3.0" );
	util::cfg::get("system").addNode("GingaNCL").addValue( "version", "", "Ginga.ar 2.0" );
}

REGISTER_INIT_CONFIG(user) {
		root().addNode( "user" )
			.addValue( "age", "", "" )
			.addValue( "location", "", "" )
			.addValue( "genre", "", "" );
}

REGISTER_INIT_CONFIG(defaults) {
		root().addNode( "default" )
			.addValue( "focusBorderColor", "", "white" )
			.addValue( "selBorderColor", "", "white" )
			.addValue( "focusBorderWidth", "", -3 )
			.addValue( "focusBorderTransparency", "", "0" );
}

REGISTER_INIT_CONFIG(service) {
	root().addNode( "service" )
			.addValue( "currentFocus", "", 0 )
			.addValue( "currentKeyMaster", "", "" );
}

REGISTER_INIT_CONFIG(si) {
	root().addNode( "si" )
			.addValue( "numberOfServices", "", 0 )
			.addValue( "numberOfPartialServices", "", 0 )
			.addValue( "channelNumber", "", 0 );
}

REGISTER_INIT_CONFIG(channel) {
	root().addNode( "channel" )
		.addValue( "keyCapture", "", "" )
		.addValue( "virtualKeyboard", "", "" )
		.addValue( "keyboardBounds", "", "" );
}

REGISTER_INIT_CONFIG(settings) {
	root().addNode( "settings" )
	.addValue( "focusBorderTransparencyAsFloat", "", 0.0f );
}

static bool checkFloat( const std::string &value, float &f ) {
	std::string v = value;
	boost::trim( v );
	bool percentual = v.find( "%" ) == v.size() - 1;
	if (percentual) {
		boost::trim_right_if( v, boost::is_any_of( "%" ) );
	}
	try {
		f = boost::lexical_cast<float>( v );
	} catch (boost::bad_lexical_cast &) {
		return false;
	}
	f = percentual ? f/100 : f;
	return true;
}


namespace player {
namespace settings {

typedef struct {
	prefix::type type;
	const char *name;
} PrefixType;

#define DO_ENUM_PREFIX_NAMES(t, s) { prefix::t, s },
static PrefixType prefixes[] = {
	{prefix::unknown, "unknown"},
	PREFIX_LIST(DO_ENUM_PREFIX_NAMES)
	{prefix::LAST, NULL}
};
#undef DO_ENUM_PREFIX_NAMES

void init( void ) {
	util::cfg::get().addNode( "global" );
	util::cfg::get().addNode( "shared" );

	char tmp[50];

	snprintf( tmp, sizeof(tmp), "(%d, %d)",
			util::cfg::getValue<int>("gui.window.size.width"),
			util::cfg::getValue<int>("gui.window.size.height") );
	std::string windowSize = std::string( tmp, 10 );

	snprintf( tmp, sizeof(tmp), "(%d, %d)",
				util::cfg::getValue<int>("gui.canvas.size.width"),
				util::cfg::getValue<int>("gui.canvas.size.height") );
	std::string canvasSize = std::string( tmp, 10 );

	util::cfg::PropertyNode &sys = util::cfg::get( "system" );
	sys.set( "screenSize", windowSize );
	sys.set( "screenSize(0)", windowSize );
	sys.set( "screenGraphicSize", canvasSize );
	sys.set( "screenGraphicSize(0)", canvasSize );

	util::cfg::PropertyNode &dft = util::cfg::get( "default" );
	dft.set( "focusBorderColor", "white" );
	dft.set( "selBorderColor", "white" );
	dft.set( "focusBorderWidth", -3 );
	dft.set( "focusBorderTransparency", "0" );

	util::cfg::get( "settings" ).set( "focusBorderTransparencyAsFloat", 0.0f );
}

void fin( void ) {
	util::cfg::get().removeNode( "global" );
	util::cfg::get().removeNode( "shared" );
}

typedef struct
{
	prefix::type prefix;
	std::string prefixName;
	std::string varName;
} Property;

Property property( const std::string &value ) {

	Property p;
	p.prefix = prefix::unknown;
	p.varName = "";

	std::vector<std::string> tokens;
	boost::split( tokens, value, boost::is_any_of( "." ) );

	p.prefixName = tokens[0];
	if (tokens.size() == 2) {
		p.varName = tokens[1];
	}

	int i = 0;
	while (prefixes[i].name) {
		if (tokens[0] == prefixes[i].name) {
			p.prefix = prefixes[i].type;
		}
		i++;
	}
	return p;
}

namespace impl {
static std::vector<Module *> luaListeners;
}

void addListener( Module *module ) {
	impl::luaListeners.push_back( module );
}

void delListener( Module *module ) {
	std::vector<Module *>::iterator it = std::find( impl::luaListeners.begin(), impl::luaListeners.end(), module );
	if (it != impl::luaListeners.end()) {
		impl::luaListeners.erase( it );
	}
}

void updateListeners() {
	BOOST_FOREACH( Module *m, impl::luaListeners ) {
		m->update();
	}
}

void setProperty( const std::string &name, const std::string &value, bool init /*=false*/) {

	LDEBUG("Player::settings", "set property, name=%s, value='%s'", name.c_str(), value.c_str());

	Property p = property( name );

	switch ( p.prefix ) {
		case prefix::unknown: {
			if (init) {
				util::cfg::get( "global" ).addValue( name, "", value );
			} else {
				util::cfg::get( "global" ).set( name, value );
			}
			break;
		}
		case prefix::system:
		case prefix::user:
		case prefix::si: {
			if (value != "") {
				LERROR("Player::settings", "%s is a read only group of environment variables", p.prefixName.c_str());
			}
			break;
		}
		case prefix::shared: {
			if (init) {
				if (!p.varName.empty()) {
					util::cfg::get( "shared" ).addValue( p.varName, "", value );
				}
			} else {
				util::cfg::setValue( name, value );
			}
			updateListeners();
			break;
		}
		case prefix::defaults: {
			if (!value.empty()) {
				if (p.varName == "focusBorderColor" || p.varName == "selBorderColor") {
					canvas::Color tmp;
					if (canvas::color::get( value.c_str(), tmp )) {
						util::cfg::setValue( name, value );
					} else {
						LWARN("Player::settings", "invalid %s, value=%s", p.varName.c_str(), value.c_str());
					}
				} else if (p.varName == "focusBorderWidth") {
					util::cfg::get().setStr( name, value );
				} else if (p.varName == "focusBorderTransparency") {
					float tmp = 0.0;
					if (checkFloat( value, tmp )) {
						util::cfg::setValue( "settings.focusBorderTransparencyAsFloat", tmp );
						util::cfg::setValue( name, value );
					}
				}
				updateListeners();
			}
			break;
		}
		case prefix::service:
		case prefix::channel: {
			if (!value.empty()) {
				if (p.varName == "currentFocus") {
					util::cfg::setValue( name, boost::lexical_cast<int>( value ) );
				} else {
					util::cfg::setValue( name, value );
				}
				updateListeners();
			}
			break;
		}
		default:
			break;
	}
}

const std::string getProperty( const std::string &name ) {

	Property p = property( name );
	std::string value = "";

	switch ( p.prefix ) {
		case prefix::unknown: {
			value = util::cfg::get( "global" ).get<std::string>( name );
			break;
		}
		default: {
			value = util::cfg::get().asString( name );
			break;
		}
	};

	LDEBUG("Player::settings", "get var, name=%s, value=%s", name.c_str(), value.c_str());
	return value;
}


}
}
