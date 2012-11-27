#include "process.h"
#include "../../../src/log.h"
#include "../../../src/process/process.h"
#include <gtest/gtest.h>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#ifdef _WIN32
#include <windows.h>
#endif

namespace fs = boost::filesystem;

void Process::SetUp( void ) {
	util::log::init();
}

void Process::TearDown( void ) {
	util::log::fin();
}

std::string getTestFile( const std::string &file ) {
	const char *root=getenv( "DEPOT" );
	if (!root) {
		root = "/";
	}
	fs::path path(root);
	path /= "lib";
	path /= "dtv-util";
	path /= "test";
	path /= "resources";
	path /= file.c_str();
	
	return path.string();
}

TEST_F( Process, default_constructor ) {
	util::Process proc(getTestFile("loop_echo.py"));

	ASSERT_TRUE( proc.pid() == INVALID_PROCESS_ID );
}

TEST_F( Process, constructor ) {
	util::Process proc(getTestFile("loop_echo.py"));
	proc.addToEnvironment("VAR","/home/path");
	proc.addToEnvironment("VAR2","/home/path2:/etc/path3");

	ASSERT_TRUE( proc.pid() == INVALID_PROCESS_ID );
}

TEST_F( Process, spawn_kill ) {
	util::Process proc(getTestFile("loop_echo.py"));

	ASSERT_TRUE( proc.run() );

	ASSERT_TRUE( proc.isRunning() );
	ASSERT_TRUE( proc.pid() != INVALID_PROCESS_ID );

	boost::this_thread::sleep( boost::posix_time::milliseconds(1000) );

	proc.kill(0);
	ASSERT_FALSE( proc.isRunning() );
	ASSERT_TRUE( proc.pid() == INVALID_PROCESS_ID );
}

TEST_F( Process, test_isRunning ) {
	util::Process proc(getTestFile("spawn.py"));

	ASSERT_TRUE( proc.run() );

	ASSERT_TRUE( proc.isRunning() );
	ASSERT_TRUE( proc.pid() != INVALID_PROCESS_ID );

	boost::this_thread::sleep( boost::posix_time::milliseconds(500) );

	ASSERT_TRUE( fs::exists( "ok.spawn" ));
	fs::remove("ok.spawn");

	boost::this_thread::sleep( boost::posix_time::milliseconds(500) );

	ASSERT_FALSE( proc.isRunning() );
	ASSERT_TRUE( proc.pid() == INVALID_PROCESS_ID );
}

TEST_F( Process, spawn_inexistent_file ) {
	util::Process proc(getTestFile("wrong_file"));

	ASSERT_FALSE( proc.run() );
}

TEST_F( Process, spawn_with_params_and_env ) {
	util::Process proc(getTestFile("test_vars.py"));

	proc.addParam("parameter1");
	proc.addParam("parameter2");
	proc.addToEnvironment("VAR=/home/path");
	proc.addToEnvironment("VAR2=/home/path2:/etc/path3");

	ASSERT_TRUE( proc.run() );

	ASSERT_TRUE( proc.pid() != INVALID_PROCESS_ID );
	ASSERT_TRUE( proc.isRunning() );
	
	boost::this_thread::sleep( boost::posix_time::milliseconds(500) );

	ASSERT_FALSE( proc.isRunning() );

	ASSERT_TRUE( fs::exists( "ok.env" ));
	fs::remove("ok.env");
	ASSERT_TRUE( fs::exists( "ok.vars" ));
	fs::remove("ok.vars");
}

TEST_F( Process, spawn_with_params_and_env2 ) {
	util::Process proc(getTestFile("test_vars.py"));

	proc.addParam("parameter1");
	proc.addParam("parameter2");
	proc.addToEnvironment("VAR", "/home/path");
	proc.addToEnvironment("VAR2", "/home/path2:/etc/path3");

	ASSERT_TRUE( proc.run() );

	ASSERT_TRUE( proc.pid() != INVALID_PROCESS_ID );
	ASSERT_TRUE( proc.isRunning() );
	
	boost::this_thread::sleep( boost::posix_time::milliseconds(500) );

	ASSERT_FALSE( proc.isRunning() );

	ASSERT_TRUE( fs::exists( "ok.env" ));
	fs::remove("ok.env");
	ASSERT_TRUE( fs::exists( "ok.vars" ));
	fs::remove("ok.vars");
}

TEST_F( Process, spawn_with_params_in_constructor ) {
	Params params;
	params.push_back("parameter1");
	params.push_back("parameter2");

	util::Process proc( getTestFile("test_vars.py"), params );
	proc.addToEnvironment("VAR=/home/path");
	proc.addToEnvironment("VAR2=/home/path2:/etc/path3");

	ASSERT_TRUE( proc.run() );

	ASSERT_TRUE( proc.pid() != INVALID_PROCESS_ID );
	ASSERT_TRUE( proc.isRunning() );
	
	boost::this_thread::sleep( boost::posix_time::milliseconds(500) );

	ASSERT_FALSE( proc.isRunning() );

	ASSERT_TRUE( fs::exists( "ok.env" ));
	fs::remove("ok.env");
	ASSERT_TRUE( fs::exists( "ok.vars" ));
	fs::remove("ok.vars");
}

TEST_F( Process, spawn_with_params_and_env_in_constructor ) {
	Params params;
	params.push_back("parameter1");
	params.push_back("parameter2");
	Environment env;
	env["VAR"] = "/home/path";
	env["VAR2"] = "/home/path2:/etc/path3";

	util::Process proc( getTestFile("test_vars.py"), params, env );

	ASSERT_TRUE( proc.run() );

	ASSERT_TRUE( proc.pid() != INVALID_PROCESS_ID );
	ASSERT_TRUE( proc.isRunning() );
	
	boost::this_thread::sleep( boost::posix_time::milliseconds(500) );

	ASSERT_FALSE( proc.isRunning() );

	ASSERT_TRUE( fs::exists( "ok.env" ));
	fs::remove("ok.env");
	ASSERT_TRUE( fs::exists( "ok.vars" ));
	fs::remove("ok.vars");
}

TEST_F( Process, spawn_with_env_in_constructor ) {
	Environment env;
	env["VAR"] = "/home/path";
	env["VAR2"] = "/home/path2:/etc/path3";

	util::Process proc( getTestFile("test_vars.py"), env );
	proc.addParam("parameter1");
	proc.addParam("parameter2");

	ASSERT_TRUE( proc.run() );

	ASSERT_TRUE( proc.pid() != INVALID_PROCESS_ID );
	ASSERT_TRUE( proc.isRunning() );
	
	boost::this_thread::sleep( boost::posix_time::milliseconds(500) );

	ASSERT_FALSE( proc.isRunning() );

	ASSERT_TRUE( fs::exists( "ok.env" ));
	fs::remove("ok.env");
	ASSERT_TRUE( fs::exists( "ok.vars" ));
	fs::remove("ok.vars");
}

TEST_F( Process, spawn_kill_spawn ) {
	util::Process proc(getTestFile("test_vars.py"));

	proc.addParam("bla");
	proc.addParam("blabla");
	proc.addToEnvironment("VAR", "blabla");
	proc.addToEnvironment("VAR2", "blablabla");

	ASSERT_TRUE( proc.run() );
	ASSERT_TRUE( proc.pid() != INVALID_PROCESS_ID );
	ASSERT_TRUE( proc.isRunning() );
	
	proc.kill();
	ASSERT_FALSE( proc.isRunning() );
	ASSERT_TRUE( proc.pid() == INVALID_PROCESS_ID );

	proc.clearParams();
	proc.clearEnvironment();

	proc.addParam("parameter1");
	proc.addParam("parameter2");
	proc.addToEnvironment("VAR", "/home/path");
	proc.addToEnvironment("VAR2", "/home/path2:/etc/path3");

	ASSERT_TRUE( proc.run() );
	ASSERT_TRUE( proc.pid() != INVALID_PROCESS_ID );
	ASSERT_TRUE( proc.isRunning() );

	boost::this_thread::sleep( boost::posix_time::milliseconds(500) );

	ASSERT_TRUE( fs::exists( "ok.env" ));
	fs::remove("ok.env");
	ASSERT_TRUE( fs::exists( "ok.vars" ));
	fs::remove("ok.vars");

	ASSERT_FALSE( proc.isRunning() );
	ASSERT_TRUE( proc.pid() == INVALID_PROCESS_ID );
}
