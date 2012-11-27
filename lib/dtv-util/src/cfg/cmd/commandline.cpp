#include "../cfg.h"
#include "commandline.h"
#include "../../log.h"
#include "../../string.h"
#include <stdexcept>
#include <assert.h>
#include <stdio.h>

namespace util {
namespace cfg {
namespace cmd {
namespace impl {

struct Finder {
	std::string _name;
	Getter _getter;
	Finder( const std::string &name, const Getter &getter ) : _name(name) {
		_getter = getter;
	}
	bool operator()( const OptionPtr &opt ) const {
		return boost::bind(_getter, opt) () == _name;
	}
};

static inline std::vector<OptionPtr>::iterator find( std::vector<OptionPtr> &opts, const std::string &name, const Getter &getter ) {
	return std::find_if( opts.begin(), opts.end(), Finder(name, getter) );
}

}

CommandLine::CommandLine( int argc, char *argv[] ) {
	_argc = argc;
	_argv = argv;
}

CommandLine::~CommandLine() {
	CLEAN_ALL(Option *, _opts);
}

bool CommandLine::parse() {
	bool result = true;
	try {
		doParse();
	} catch (const std::runtime_error & e) {
		printf("%s \n", e.what());
		result = false;
	}
	return result;
}

void CommandLine::doParse() {
	int cur = 1;
	Option *opt;
	while (cur < _argc) {
		assert(_argv[cur]);
		std::string str(_argv[cur]);
		if (!( str[0] == '-' )) {
			throw std::runtime_error( "bad format of command line option: Options must begin with single or double hyphen " );
		}
		opt = getOption(str.substr(0, str.find( "=" )));
		if (opt) {
			set(opt);
			if (( str[1] == '-' ) && ( str.find( "=" ) != std::string::npos )) {
				opt->set(str.substr(str.find( "=" )+1));
			} else {
				//	Parse argument if any.
				if (( cur + 1 < _argc ) && (( *_argv[cur + 1] ) != '-' )) {
					opt->set(_argv[cur+1]);
					cur++;
				} else {
					opt->set();
				}
			}
		} else {
			throw std::runtime_error( "It is not an option known: " + str.substr(0, str.find( "=" )));
		}
		cur++;
	}
}

Option *CommandLine::getOption( const std::string &name ) {
	Option *opt = NULL;
	if (name[1] == '-') {
		opt = searchOpt(_opts, name.substr(2,name.length()),&Option::alias);
	} else {
		opt = searchOpt(_opts, name.substr(1,name.length()),&Option::snamestr);
	}
	return opt;
}

Option *CommandLine::searchOpt( std::vector<Option *> vec, const std::string &name, const impl::Getter &getter ) {
	Option *opt = NULL;
	std::vector<Option *>::iterator it = impl::find(vec, name, getter);
	if (it != vec.end()) {
		opt = ( *it );
	}
	return opt;
}

void CommandLine::set( Option *opt ) {
	_setOpts.push_back( opt );
}

void CommandLine::registerOpt( const std::string &prop, const std::string &alias, char shortName ) {
	checkValues(prop, alias, shortName);
	Option *opt = new Option(prop,alias);
	if (opt->exists()) {
		if (shortName) {
			opt->setsname(shortName);
		}
		_opts.push_back(opt);
	} else {
		delete opt;
		throw std::runtime_error("The option is not a config value: " + opt->property());
	}
}

void CommandLine::noShowDefault( const std::string &alias ) {
	Option *opt = searchOpt(_opts, alias, &Option::alias);
	if (opt) {
		opt->noShowDefault();
	} else {
		throw std::runtime_error("The property is not registered: " + alias);
	}
}

void CommandLine::checkValues( const std::string &prop, const std::string &alias, char shortName ) {
	std::string sname(1,shortName);
	if (isRegistered(prop, &Option::property)) {
		throw std::runtime_error("The property is already registered: " + prop);
	} else if (isRegistered(alias, &Option::alias)) {
		throw std::runtime_error("The option's name is already is use: " + alias);
	} else if (isRegistered(sname, &Option::snamestr)) {
		throw std::runtime_error("The short name is already is use: " + sname);
	}
}

bool CommandLine::isRegistered( const std::string &name, const impl::Getter &getter ) {
	return ( searchOpt(_opts, name, getter) != NULL );
}

bool CommandLine::isRegistered( const std::string &name) {
	return isRegistered( name, &Option::alias );
}

bool CommandLine::isRegistered( const char name ) {
	return isRegistered( std::string(1,name), &Option::snamestr );
}

bool CommandLine::isSet( const std::string &name) {
	return ( searchOpt(_setOpts, name, &Option::alias) != NULL );
}

#define MAX_SIZE( m, s ) if (m < s) m=s;
const std::string CommandLine::desc() const {
	std::string tab = "  ";
	std::string defaultStr = "{default}";
	std::string result;
	int maxName = 0;
	int maxDef = defaultStr.length();
	int maxLength = 30;

	BOOST_FOREACH( Option *opt, _opts ) {
		MAX_SIZE( maxName,  (int) opt->alias().length() );
		if ( (int) opt->def().length() <= maxLength) {
			MAX_SIZE( maxDef,  (int) opt->def().length() );
		}
	}
	
	BOOST_FOREACH( Option *opt, _opts ) {
		std::string str = tab;
		if (opt->hasShortName()) {
			str += "-" + opt->snamestr() + ", ";
		}
		str += "--" + opt->alias();
		if (!opt->def().empty() ) {
			str += "=";
			if ( (int) opt->def().length() < maxLength) {
				str += opt->def();
			} else {
				str += defaultStr;
			}
		}
		std::string aux = format("%%-%ds", maxName+maxDef+8+tab.length());
		result += format(aux.c_str(), str.c_str());
		result += opt->desc() + "\n";
	}
	return result;
}

}
}
}
