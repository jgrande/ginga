#include <string>
#include "configregistrator.h"
#include "../../../src/cfg/configregistrator.h"
#include "../../../src/cfg/cfg.h"

REGISTER_INIT_CONFIG( tuner_provider ) {
	root().addNode( "provider" );
}

REGISTER_INIT_CONFIG( tuner_dep ) {
	std::string ip("192.168.0.66");
	root().addNode( "dep" ).addValue("ip","desc",ip);
}

REGISTER_INIT_CONFIG( tuner_provider_dvb ) {
	std::string ip("192.168.0.224");
	root().addNode( "dvb" ).addValue("ip","desc",ip);
}

REGISTER_INIT_CONFIG( tuner_provider_dvb_dep ) {
	root().addNode( "dep" ).addValue("on","desc",true);
}

REGISTER_INIT_CONFIG( tuner ) {
	root().addNode("tuner");
}

REGISTER_INIT_CONFIG( lib ) {
	root().addNode("lib").addValue("val","desc",false);
}

REGISTER_INIT_CONFIG( config ) {
	root().addNode("config").addNode("lib").addValue("val","desc",false);
	root()("config").addValue("configval","desc",false);
}


REGISTER_FIN_CONFIG( config_lib ) {
	root().removeNode("lib");
}

REGISTER_FIN_CONFIG( config ) {
	root()("config").removeProp("configval");
}

ConfigRegistrator::ConfigRegistrator()
{
}

ConfigRegistrator::~ConfigRegistrator() {
}

void ConfigRegistrator::SetUp( void ) {
	util::reg::init();
	util::reg::fin();
}

void ConfigRegistrator::TearDown( void ) {

}

TEST_F( ConfigRegistrator, register_node ) {
	ASSERT_TRUE( util::cfg::get().hasChild("tuner") );
}

TEST_F( ConfigRegistrator, register_fin ) {
	ASSERT_FALSE(util::cfg::get("config").hasChild("lib"));
	ASSERT_FALSE(util::cfg::get("config").existsValue("configval"));
}

TEST_F( ConfigRegistrator, register_node_and_value ) {
	ASSERT_TRUE( util::cfg::get().hasChild("lib") );
	ASSERT_TRUE( util::cfg::get("lib").existsValue("val") );
}

TEST_F( ConfigRegistrator, with_deps ) {
	ASSERT_TRUE( util::cfg::get("tuner").hasChild("provider") );
	ASSERT_TRUE( util::cfg::get("tuner").hasChild("dep") );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tuner.dep.ip") == "192.168.0.66" );
	ASSERT_TRUE( util::cfg::get("tuner.provider").hasChild("dvb") );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("tuner.provider.dvb.ip") == "192.168.0.224" );
	ASSERT_TRUE( util::cfg::getValue<bool> ("tuner.provider.dvb.dep.on") );
}

TEST_F(ConfigRegistrator, initAgain){
	ASSERT_NO_THROW(util::reg::init());

}
