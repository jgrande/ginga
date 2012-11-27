#pragma once

#include <string>

namespace util {
namespace cfg {
namespace cmd {

class Option {
public:
	Option( const std::string &prop, const std::string &alias="" );
	virtual ~Option();

	void setsname( char sname );
	void noShowDefault();
	void showDefault();

	// Queries
	char sname() const;
	const std::string &snamestr() const;
	const std::string &property() const;
	const std::string &alias() const;
	const std::string def() const;
	const std::string desc();
	bool hasShortName() const;
	bool exists() const;

	virtual void set();
	virtual void set( const std::string &str );

private:
	std::string _path;
	std::string _alias;
	std::string _sname;
	bool _showDef;
};

}
}
}

