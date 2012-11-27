#include <iostream>
#include <gtest/gtest.h>
#include "../../src/registrator.h"
#include "../../src/tool.h"
#include "../../src/cfg/cmd/commandline.h"
#include "../../src/cfg/propertynode.h"


class ToolExtension : public util::Tool {
public:
	ToolExtension( const std::string &name, const std::string &desc, const std::string &version = "1.0.0", const std::string &build = "0" );
	virtual ~ToolExtension();

	void pretend();
	void defaults();
	int execute( int argc, char *argv[] );
	util::cfg::PropertyTree &getCfg();
	std::string getBufAsString() const;
protected:
	virtual void registerProperties( util::cfg::cmd::CommandLine &cmd );

	template <typename T>
	void registerProp( const std::string &prop,const char /*sname*/, const std::string &desc, T val, util::cfg::cmd::CommandLine /*&cmd*/ );

	template <typename T>
	void registerProp( const std::string &prop, const std::string &desc, T val, util::cfg::cmd::CommandLine /*&cmd*/ );

	private:
	std::stringbuf *_buf;
	std::ostream *_anOstream;
	util::cfg::PropertyTree _cfg;

};

template <typename T>
void ToolExtension::registerProp( const std::string &prop, const std::string &desc, T val, util::cfg::cmd::CommandLine /*&cmd*/ ) {
	getCfg().addValue(prop, desc, val);
}

template <typename T>
void ToolExtension::registerProp( const std::string &prop,const char /*sname*/, const std::string &desc, T val, util::cfg::cmd::CommandLine /*&cmd*/ ) {
	getCfg().addValue(prop, desc, val);
}

class ToolExtensionTest: public testing::Test{
public:
	ToolExtensionTest();
	virtual ~ToolExtensionTest();
protected:
	virtual void SetUp( void );
	virtual void TearDown( void );

	char **_params;
	std::list<util::reg::Registrator *> _list;
	ToolExtension *_tool;
};

