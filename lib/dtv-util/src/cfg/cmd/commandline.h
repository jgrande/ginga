#pragma once

#include "option.h"
#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <string>
#include <vector>

namespace util {
namespace cfg {
namespace cmd {


namespace impl {
typedef Option *OptionPtr;
typedef const std::string & ( Option::*Getter )( void ) const;
}

class CommandLine {
public:
	CommandLine( int argc, char *argv[] );
	virtual ~CommandLine();

	bool parse();
	void registerOpt( const std::string &prop, const std::string &alias, char shortName=0 );
	void noShowDefault( const std::string &alias );

	bool isSet( const std::string &name );
	bool isRegistered( const std::string &name );
	bool isRegistered( const char name );

	const std::string desc() const;

protected:
	void doParse();

	void set( Option *opt );

	Option *getOption( const std::string &str );
	Option *searchOpt( std::vector<Option *> vec, const std::string &name, const impl::Getter &getter );
	void checkValues( const std::string &prop, const std::string &alias, char shortName );
	bool isRegistered( const std::string &name, const impl::Getter &getter);

private:
	std::vector<Option *> _opts;
	std::vector<Option *> _setOpts;
	char **_argv;
	int _argc;
};

}
}
}

