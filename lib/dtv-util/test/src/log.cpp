#include "log.h"
#include "../../src/cfg/cfg.h"
#include "../../src/log.h"
#include <boost/filesystem.hpp>
#include <fstream>

namespace fs = boost::filesystem;

#define doLogArgs( c )							\
	LINFO(c, "Mensaje de prueba con args: %c", 'A');		\
	LINFO(c, "Mensaje de prueba con args: %d", 1);			\
	LINFO(c, "Mensaje de prueba con args: %i", -1);			\
	LINFO(c, "Mensaje de prueba con args: %o", 0172);		\
	LINFO(c, "Mensaje de prueba con args: %0.2f", 1.255f);		\
	LINFO(c, "Mensaje de prueba con args: %0.2e", 0.0123e+2);	\
	LINFO(c, "Mensaje de prueba con args: %0.2E", 0.0123E+2);	\
	LINFO(c, "Mensaje de prueba con args: %x", 0x1f);		\
	LINFO(c, "Mensaje de prueba con args: %X", 0x1f);		\
	LINFO(c, "Mensaje de prueba con args: %s", "hola");

#define doLog( c ) 			\
	LTRACE(c, "Mensaje de prueba");	\
	LDEBUG(c, "Mensaje de prueba");	\
	LINFO(c, "Mensaje de prueba");	\
	LWARN(c, "Mensaje de prueba");	\
	LERROR(c, "Mensaje de prueba");

#define doLogGroup( g, c ) 					\
	LOG_TRACE( g, c, "Mensaje de prueba" );	\
	LOG_DEBUG( g, c, "Mensaje de prueba" );	\
	LOG_INFO( g, c, "Mensaje de prueba" );	\
	LOG_WARN( g, c, "Mensaje de prueba" );	\
	LOG_ERROR( g, c, "Mensaje de prueba" );

LoggerTest::LoggerTest() {
	const char *root=getenv( "DEPOT" );
	if (!root) {
		root = "/";
	}
	fs::path path(root);
	path /= "lib";
	path /= "dtv-util";
	path /= "test";
	path /= "resources";
	path /= "test.log";
	_file = path.string();
}

void LoggerTest::SetUp( void ) {
	util::cfg::get("log").set<bool>("enabled", true);
	util::cfg::get("log.filter.all").set<std::string>("all", std::string("info"));
	util::cfg::get("log.output.stdout").set<bool>("use", true);
	util::cfg::get("log.output.file").set<bool>("use", true);
	util::cfg::get("log.output.file").set<std::string>("filename", _file);
}

TEST_F(LoggerTest, basic) {
	util::log::init();
	doLog("test");
	util::log::fin();

	std::string line;
	std::ifstream ifile(_file.c_str());
	ASSERT_TRUE( ifile.is_open() );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 15) == "Log started at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] WARNING: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] ERROR: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 13) == "Log ended at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line.empty() );
	ASSERT_TRUE( ifile.eof() );

	ifile.close();
	fs::remove(_file);
}

TEST_F(LoggerTest, basic_without_category) {
	util::log::init();
	LDEBUG("", "Mensaje de prueba");
	LINFO("", "Mensaje de prueba");
	LWARN("", "Mensaje de prueba");
	LERROR("", "Mensaje de prueba");
	util::log::fin();

	std::string line;
	std::ifstream ifile(_file.c_str());
	ASSERT_TRUE( ifile.is_open() );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 15) == "Log started at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util] Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util] WARNING: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util] ERROR: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 13) == "Log ended at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line.empty() );
	ASSERT_TRUE( ifile.eof() );

	ifile.close();
	fs::remove(_file);
}

TEST_F(LoggerTest, basic_args) {
	util::log::init();
	doLogArgs("test");
	util::log::fin();

	std::string line;
	std::ifstream ifile(_file.c_str());
	ASSERT_TRUE( ifile.is_open() );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 15) == "Log started at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba con args: A" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba con args: 1" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba con args: -1" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba con args: 172" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba con args: 1.25" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba con args: 1.23e+00" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba con args: 1.23E+00" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba con args: 1f" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba con args: 1F" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba con args: hola" );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 13) == "Log ended at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line.empty() );
	ASSERT_TRUE( ifile.eof() );

	ifile.close();
	fs::remove(_file);
}

TEST_F(LoggerTest, basic_all) {
	util::cfg::get("log.filter.all").set<std::string>("all", std::string("all"));
	util::log::init();
	doLog("test");
	util::log::fin();

	std::string line;
	std::ifstream ifile(_file.c_str());
	ASSERT_TRUE( ifile.is_open() );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 15) == "Log started at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] TRACE: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] DEBUG: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] WARNING: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] ERROR: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 13) == "Log ended at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line.empty() );
	ASSERT_TRUE( ifile.eof() );

	ifile.close();
	fs::remove(_file);
}

TEST_F(LoggerTest, basic_trace) {
	util::cfg::get("log.filter.all").set<std::string>("all", std::string("trace"));
	util::log::init();
	doLog("test");
	util::log::fin();

	std::string line;
	std::ifstream ifile(_file.c_str());
	ASSERT_TRUE( ifile.is_open() );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 15) == "Log started at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] TRACE: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] DEBUG: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] WARNING: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] ERROR: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 13) == "Log ended at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line.empty() );
	ASSERT_TRUE( ifile.eof() );

	ifile.close();
	fs::remove(_file);
}

TEST_F(LoggerTest, basic_debug) {
	util::cfg::get("log.filter.all").set<std::string>("all", std::string("debug"));
	util::log::init();
	doLog("test");
	util::log::fin();

	std::string line;
	std::ifstream ifile(_file.c_str());
	ASSERT_TRUE( ifile.is_open() );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 15) == "Log started at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] DEBUG: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] WARNING: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] ERROR: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 13) == "Log ended at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line.empty() );
	ASSERT_TRUE( ifile.eof() );

	ifile.close();
	fs::remove(_file);
}

TEST_F(LoggerTest, basic_warn) {
	util::cfg::get("log.filter.all").set<std::string>("all", std::string("warn"));
	util::log::init();
	doLog("test");
	util::log::fin();

	std::string line;
	std::ifstream ifile(_file.c_str());
	ASSERT_TRUE( ifile.is_open() );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 15) == "Log started at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] WARNING: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] ERROR: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 13) == "Log ended at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line.empty() );
	ASSERT_TRUE( ifile.eof() );

	ifile.close();
	fs::remove(_file);
}

TEST_F(LoggerTest, basic_err) {
	util::cfg::get("log.filter.all").set<std::string>("all", std::string("error"));
	util::log::init();
	doLog("test");
	util::log::fin();

	std::string line;
	std::ifstream ifile(_file.c_str());
	ASSERT_TRUE( ifile.is_open() );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 15) == "Log started at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] ERROR: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 13) == "Log ended at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line.empty() );
	ASSERT_TRUE( ifile.eof() );

	ifile.close();
	fs::remove(_file);
}

TEST_F(LoggerTest, basic_none) {
	util::cfg::get("log.filter.all").set<std::string>("all", std::string("none"));
	util::log::init();
	doLog("test");
	util::log::fin();

	ASSERT_FALSE( fs::exists( _file ));
}

TEST_F(LoggerTest, basic_disabled) {
	util::cfg::get("log").set<bool>("enabled", false);
	util::log::init();
	doLog("test");
	util::log::fin();

	ASSERT_FALSE( fs::exists( _file ));
}

TEST_F(LoggerTest, groups_and_categories) {
	util::cfg::get("log.filter.all").set<std::string>("all", std::string("error"));
	util::cfg::get("log.filter").addNode("grupo1").addValue<std::string>("all", std::string("warn"));
	util::cfg::get("log.filter.grupo1").addValue<std::string>("categoria2", std::string("info"));
	util::cfg::get("log.filter").addNode("grupo2").addValue<std::string>("all", std::string("all"));

	util::log::init();
	doLog("test");
	doLogGroup( "grupo1", "categoria1");
	doLogGroup( "grupo1", "categoria2");
	doLogGroup( "grupo2", "categoria1");
	util::log::fin();

	std::string line;
	std::ifstream ifile(_file.c_str());
	ASSERT_TRUE( ifile.is_open() );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 15) == "Log started at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] ERROR: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[grupo1::categoria1] WARNING: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[grupo1::categoria1] ERROR: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[grupo1::categoria2] Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[grupo1::categoria2] WARNING: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[grupo1::categoria2] ERROR: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[grupo2::categoria1] TRACE: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[grupo2::categoria1] DEBUG: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[grupo2::categoria1] Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[grupo2::categoria1] WARNING: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[grupo2::categoria1] ERROR: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 13) == "Log ended at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line.empty() );
	ASSERT_TRUE( ifile.eof() );

	ifile.close();
	fs::remove(_file);

	util::cfg::get("log.filter").removeNode("grupo1");
	util::cfg::get("log.filter").removeNode("grupo2");
}

TEST_F(LoggerTest, flush) {
	util::cfg::get("log.filter.all").set<std::string>("all", std::string("all"));
	util::log::init();

	doLog("test");
	util::log::flush();

	std::string line;
	std::ifstream ifile(_file.c_str());
	ASSERT_TRUE( ifile.is_open() );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 15) == "Log started at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] TRACE: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] DEBUG: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] WARNING: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] ERROR: Mensaje de prueba" );

	util::log::fin();

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 13) == "Log ended at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line.empty() );
	ASSERT_TRUE( ifile.eof() );

	ifile.close();
	fs::remove(_file);
}

TEST_F(LoggerTest, all_group_specific_category) {
	util::cfg::get("log.filter.all").set<std::string>("all", std::string("none"));
	util::cfg::get("log.filter.all").addValue<std::string>("test", std::string("all"));

	util::log::init();
	doLog("cat");
	doLog("test");
	util::log::fin();

	std::string line;
	std::ifstream ifile(_file.c_str());
	ASSERT_TRUE( ifile.is_open() );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 15) == "Log started at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] TRACE: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] DEBUG: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] WARNING: Mensaje de prueba" );
	std::getline(ifile, line);
	ASSERT_TRUE( line == "[util::test] ERROR: Mensaje de prueba" );

	std::getline(ifile, line);
	ASSERT_TRUE( line.substr(0, 13) == "Log ended at:");

	std::getline(ifile, line);
	ASSERT_TRUE( line.empty() );
	ASSERT_TRUE( ifile.eof() );

	ifile.close();
	fs::remove(_file);
}