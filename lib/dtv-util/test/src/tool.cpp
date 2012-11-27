#include <gtest/gtest.h>
#include "../../src/tool.h"
#include "functions.h"
#include "tool.h"

ToolTest::ToolTest() {
}

ToolTest::~ToolTest() {
}

void ToolTest::SetUp( void ) {
}

void ToolTest::TearDown( void ) {
	util::cfg::get().removeNode("tool");
}


TEST_F( ToolTest, constructor ) {
	util::Tool tool("genericTool","description","2.0.0","0.0.1");

	ASSERT_TRUE( tool.name() == "genericTool" );
	ASSERT_TRUE( tool.description() == "description" );
	ASSERT_TRUE( tool.version() == "2.0.0" );
	ASSERT_TRUE( tool.build() == "0.0.1" );
}

TEST_F( ToolTest, constructor_two_parameters ) {
	util::Tool tool("genericTool","description");

	ASSERT_TRUE( tool.name() == "genericTool" );
	ASSERT_TRUE( tool.description() == "description" );
	ASSERT_TRUE( tool.version() == "1.0.0" );
	ASSERT_TRUE( tool.build() == "0" );
}

TEST_F( ToolTest, execute ) {
	util::Tool tool("genericTool","description","1.0.0","version_desc");
	char **params;

	const char *argv[1] = {"programName"};
	params = util::makeParams( argv, 1 );
	ASSERT_TRUE( tool.execute( 1, params ) == 0 );
	util::deleteParams( params );
}

TEST_F( ToolTest, set_one_bool ) {
	util::Tool tool("genericTool","description","1.0.0","version_desc");
	const char *argv[2] = {"programName","--set=tool.help=true"};
	char **params = util::makeParams( argv, 2);

	ASSERT_TRUE( tool.execute( 2, params ) == 0 );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tool.set") == "tool.help=true" );
	ASSERT_TRUE( util::cfg::getValue<bool> ("tool.help") );
	util::deleteParams( params );
}

TEST_F( ToolTest, set_one_str ) {
	util::Tool tool("genericTool","description","1.0.0","version_desc");
	const char *argv[2] = {"programName","--set=tool.version=3.0"};
	char **params = util::makeParams( argv, 2);

	ASSERT_TRUE( tool.execute( 2, params ) == 0 );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tool.set") == "tool.version=3.0" );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tool.version") == "3.0" );
	util::deleteParams( params );
}

TEST_F( ToolTest, set_two ) {
	util::Tool tool("genericTool","description","1.0.0","version_desc");
	const char *argv[2] = {"programName","--set=tool.version=3.0:tool.build=Build2398"};
	char **params = util::makeParams( argv, 2);

	ASSERT_TRUE( tool.execute( 2, params ) == 0 );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tool.set") == "tool.version=3.0:tool.build=Build2398" );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tool.version") == "3.0" );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tool.build") == "Build2398" );
	util::deleteParams( params );
}

TEST_F( ToolTest, set_three ) {
	util::Tool tool("genericTool","description","1.0.0","version_desc");
	const char *argv[2] = {"programName","--set=tool.help=true:tool.version=3.0:tool.build=Build2398"};
	char **params = util::makeParams( argv, 2);

	ASSERT_TRUE( tool.execute( 2, params ) == 0 );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tool.set") == "tool.help=true:tool.version=3.0:tool.build=Build2398" );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tool.version") == "3.0" );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tool.build") == "Build2398" );
	ASSERT_TRUE( util::cfg::getValue<bool> ("tool.help") );
	util::deleteParams( params );
}

TEST_F( ToolTest, empty_set_parameters ) {
	util::Tool tool("genericTool","description","1.0.0","version_desc");
	const char *argv[2] = {"programName","--set=:tool.help=true"};
	char **params = util::makeParams( argv, 2);

	ASSERT_TRUE( tool.execute( 2, params ) == 0 );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tool.set") == ":tool.help=true" );
	ASSERT_TRUE( util::cfg::getValue<bool> ("tool.help") );
	util::deleteParams( params );
}

TEST_F( ToolTest, empty_set_parameters_two ) {
	util::Tool tool("genericTool","description","1.0.0","version_desc");
	const char *argv[2] = {"programName","--set=tool.help=true:"};
	char **params = util::makeParams( argv, 2);

	ASSERT_TRUE( tool.execute( 2, params ) == 0 );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tool.set") == "tool.help=true:" );
	ASSERT_TRUE( util::cfg::getValue<bool> ("tool.help") );
	util::deleteParams( params );
}

TEST_F( ToolTest, empty_set_parameters_three ) {
	util::Tool tool("genericTool","description","1.0.0","version_desc");
	const char *argv[2] = {"programName","--set=:tool.help=true:"};
	char **params = util::makeParams( argv, 2);

	ASSERT_TRUE( tool.execute( 2, params ) == 0 );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tool.set") == ":tool.help=true:" );
	ASSERT_TRUE( util::cfg::getValue<bool> ("tool.help") );
	util::deleteParams( params );
}

TEST_F( ToolTest, empty_set_parameters_four ) {
	util::Tool tool("genericTool","description","1.0.0","version_desc");
	const char *argv[2] = {"programName","--set=tool.help=true::"};
	char **params = util::makeParams( argv, 2);

	ASSERT_TRUE( tool.execute( 2, params ) == 0 );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tool.set") == "tool.help=true::" );
	ASSERT_TRUE( util::cfg::getValue<bool> ("tool.help") );
	util::deleteParams( params );
}
