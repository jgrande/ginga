#include "../../src/cfg/xmlparser.h"
#include "../../src/cfg/cfg.h"
#include "toolextension.h"
#include "functions.h"
#include "../../src/cfg/cfg.h"

ToolExtension::ToolExtension( const std::string &name, const std::string &desc, const std::string &version/* = "1.0.0"*/, const std::string &build/* = "0"*/	 )
: Tool( name, desc, version, build )
{
	_buf = new std::stringbuf;
	_anOstream = new std::ostream(_buf);
}

ToolExtension::~ToolExtension(){
	delete _anOstream;
	delete _buf;
}
void ToolExtension::registerProperties( util::cfg::cmd::CommandLine &cmd ) {
	getCfg().setName( name() );

	registerProp("help", 'h', "Display this message", false, cmd);

	registerProp("version", 'v', "Display tool version", false, cmd);
	registerProp("build", 'b', "Display build information", false, cmd);
	registerProp("defaults", "Show in xml format the configuration default values", false, cmd);
	registerProp("pretend", "Show in xml format the configuration pretend values", false, cmd);
}

void ToolExtension::pretend()  {
	util::cfg::XmlParser parser;
	parser.pretend(*_anOstream, &getCfg());
}

void ToolExtension::defaults() {
	util::cfg::XmlParser parser;
	parser.defaults(*_anOstream, &getCfg());
}

int ToolExtension::execute( int argc, char *argv[] ) {
	util::cfg::cmd::CommandLine cmd( argc, argv );
	registerProperties( cmd );
	return 1;
}
util::cfg::PropertyTree &ToolExtension::getCfg(){
	return _cfg;
}

std::string ToolExtension::getBufAsString() const{
	return _buf->str();
}
ToolExtensionTest::ToolExtensionTest()
{
}

ToolExtensionTest::~ToolExtensionTest()
{
}

void ToolExtensionTest::SetUp( void ){
	_tool = new ToolExtension("genericTool","description","2.0.0","0.0.1");
	const char *argv[1] = {"programName"};
	_params = util::makeParams( argv, 1 );
	_tool->execute( 1, _params );
}

void ToolExtensionTest::TearDown( void ){
	util::cfg::get().removeProp("help");
	util::cfg::get().removeProp("version");
	util::cfg::get().removeProp("build");
	util::cfg::get().removeProp("defaults");
	util::cfg::get().removeProp("pretend");
	util::deleteParams( _params );
	delete (_tool);
}


TEST_F(ToolExtensionTest, defaults){
	std::string print;
	std::string mustPrint("<?xml version=\"1.0\" encoding=\"UTF-16\" standalone=\"no\" ?>\n<genericTool>\n  <help>false</help>\n  <version>false</version>\n  <build>false</build>\n  <defaults>false</defaults>\n  <pretend>false</pretend>\n</genericTool>\n");

	_tool->defaults();
	print = _tool->getBufAsString();
	ASSERT_TRUE(print.size() > 0);
	ASSERT_TRUE(mustPrint.compare(print) == 0);

}
TEST_F(ToolExtensionTest, pretend){
	std::string print;
	std::string mustPrint("<?xml version=\"1.0\" encoding=\"UTF-16\" standalone=\"no\" ?>\n<genericTool>\n  <pretend>true</pretend>\n</genericTool>\n");
	_tool->getCfg().setStr("pretend","true");
	_tool->pretend();
	print = _tool->getBufAsString();
	ASSERT_TRUE(print.size() > 0);
	ASSERT_TRUE(mustPrint.compare(print) == 0);
}
