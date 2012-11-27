#include <string>
#include "../../../src/cfg/cfg.h"
#include "cfg.h"

Cfg::Cfg() {
}

Cfg::~Cfg() {
}

void Cfg::SetUp( void ) {
	util::cfg::get().addValue("intOpt","intOptOfRoot",20)
		.addNode("child")
		.addValue("boolOpt","boolOptOfChild",false)
		.addNode("grandson")
		.addValue("strOpt","strOptOfGrandson",std::string("str"));
	util::cfg::get().addNode("anotherChild")
		.addValue("strOpt","strOptOfAnotherChild",std::string("str"));
}

void Cfg::TearDown( void ) {
	util::cfg::get().removeNode("child");
	util::cfg::get().removeNode("anotherChild");
	util::cfg::get().removeProp("intOpt");
}


TEST_F( Cfg, get ) {
	ASSERT_TRUE( util::cfg::get().name() == "root" );
}

TEST_F( Cfg, get_with_path ) {
	ASSERT_TRUE( util::cfg::get("child").name() == "child" );
	ASSERT_TRUE( util::cfg::get("child.grandson").name() == "grandson" );
	ASSERT_TRUE( util::cfg::get("anotherChild").name() == "anotherChild" );
}

TEST_F( Cfg, getValue ) {
	ASSERT_TRUE( util::cfg::getValue<int> ("intOpt") == 20 );
	ASSERT_FALSE( util::cfg::getValue<bool> ("child.boolOpt") );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("child.grandson.strOpt") == "str" );
	ASSERT_TRUE( util::cfg::getValue<std::string> ("anotherChild.strOpt") == "str" );
}

TEST_F( Cfg, setValue ) {
	util::cfg::setValue("intOpt",10);
	ASSERT_TRUE( util::cfg::getValue<int> ("intOpt") == 10 );

	util::cfg::setValue("child.boolOpt",true);
	ASSERT_TRUE( util::cfg::getValue<bool> ("child.boolOpt") );

	util::cfg::setValue("child.grandson.strOpt",std::string("val"));
	ASSERT_TRUE( util::cfg::getValue<std::string> ("child.grandson.strOpt") == "val" );

	util::cfg::setValue("anotherChild.strOpt",std::string("val"));
	ASSERT_TRUE( util::cfg::getValue<std::string> ("anotherChild.strOpt") == "val" );
}
