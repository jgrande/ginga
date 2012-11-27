#include "debugging_aids.h"
#include "tool.h"
#include "cfg/xmlparser.h"
#include "registrator.h"
#include "log.h"
#include "generated/config.h"

#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#ifndef _WIN32
void sighandler(int sig) {
	printf("[Tool] Got signal %d\n", sig);
	util::custom_terminate();
	exit(1);
}
#endif

namespace util {

namespace fs = boost::filesystem;

Tool::Tool(const std::string &name, const std::string &desc, const std::string &version, const std::string &build)
	: _name( name ), _desc( desc ), _version( version ), _build( build ) {
}

Tool::~Tool() {
}

const std::string &Tool::name() const {
	return _name;
}

const std::string &Tool::version() const {
	return _version;
}

const std::string &Tool::build() const {
	return _build;
}

const std::string &Tool::description() const {
	return _desc;
}

void Tool::printVersion() const {
	printf("%s version %s\n",
	       name().c_str(), version().c_str() );
}

void Tool::printBuild() const {
	printf("%s\n", build().c_str() );
}

void Tool::pretend() const {
	util::cfg::XmlParser parser;
	std::stringbuf *aBuf = new std::stringbuf;
	std::ostream anOstream(aBuf);
	parser.pretend(anOstream, &cfg::get());
	printf("%s",aBuf->str().c_str());
	delete aBuf;
}
void Tool::defaults() const {
	util::cfg::XmlParser parser;
	std::stringbuf *aBuf = new std::stringbuf;
	std::ostream anOstream(aBuf);
	parser.defaults(anOstream, &cfg::get());
	printf("%s",aBuf->str().c_str());
	delete aBuf;
}

void Tool::set() const {
	std::vector<std::string> arguments;
	boost::split(arguments, cfg::getValue<std::string> ("tool.set"), boost::is_any_of(":"));
	BOOST_FOREACH( std::string arg, arguments ) {
		if (!arg.empty()) {
			if (arg.find( "=" ) != std::string::npos) {
				std::string val = arg.substr(arg.find("=")+1,arg.length());
				std::string path = arg.substr(0,arg.find("="));
				if (path.find(".") != std::string::npos) {
					std::string node = path.substr(0, path.rfind("."));
					std::string prop = path.substr(path.rfind(".")+1, path.length());
					cfg::get(node).setStr(prop, val);
				} else {
					cfg::get().setStr(path, val);
				}
			} else {
				throw std::runtime_error( "bad format of command line option: Pair of values must contain an equal symbol");
			}
		}
	}
}

const std::string &Tool::makeDescription( std::string &group, std::string &category ) const {
	std::string *desc = new std::string("Level to log for ");
	if (category == "all") {
		(*desc) += "all categories in ";
		(*desc) += group;
		(*desc) += " group";
	} else {
		(*desc) += category;
		(*desc) += " category in  ";
		(*desc) += group;
		(*desc) += " group";
	}
	return (*desc);
}

void Tool::debug() const {
	std::vector<std::string> arguments;
	boost::split(arguments, cfg::getValue<std::string> ("tool.debug"), boost::is_any_of("&"));
	BOOST_FOREACH( std::string arg, arguments ) {
		if (!arg.empty()) {
			bool badFormat = true;
			if (arg.find( "." ) != std::string::npos) {
				size_t from = 0;
				size_t to = arg.find(".");
				std::string group = arg.substr(from, to-from);
				from = to+1;
				to = arg.find(".", from);
				if (to != std::string::npos) {
					std::string category = arg.substr(from, to-from);
					from = to+1;
					to = arg.find(".", from);
					if (to == std::string::npos) {
						std::string level = arg.substr(from, to-from);
						badFormat = false;
						if (!cfg::get("log.filter").existsNode(group)) {
							cfg::PropertyNode &node = cfg::get("log.filter").addNode(group);
							if (category != "all") {
								std::string cat("all");
								node.addValue(cat, makeDescription(group, cat), "");
								node.set<std::string>(cat, cfg::getValue<std::string>("log.filter.all.all"));
							}
							node.addValue(category, makeDescription(group, category), "");
						}
						if (!cfg::get(std::string("log.filter.")+group).existsValue(category)) {
							cfg::get(std::string("log.filter.")+group).addValue(category, makeDescription(group, category), "");
						}
						cfg::get(std::string("log.filter.")+group).set<std::string>(category, level);
					}
				}
			}
			if (badFormat) {
				throw std::runtime_error( "bad format of command line debug option, format is: [group].[category].[level]");
			}
		}
	}
}

void Tool::setupSignals() const {
#ifndef _DEBUG
#ifndef _WIN32
	struct sigaction sa;
	sa.sa_handler = sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGBUS, &sa, NULL);
	sigaction(SIGILL, &sa, NULL);
#endif
	//	Setup custom debugging
	std::set_terminate( &util::custom_terminate );
#endif
}

void Tool::loadConfig() {
	util::cfg::XmlParser parser;
	BOOST_FOREACH( std::string xml, _cfgXmls ) {
		if (fs::exists(xml)) {
			fprintf(stderr, "[Tool] Load configuration from xml file: %s\n", xml.c_str());
			fs::path path(xml);
			parser.parserIn( path.string(), &cfg::get());
		}

	}
}

void Tool::addConfig( const std::string &xml ) {
	_cfgXmls.insert(xml);
}

void Tool::registerProperties( cfg::cmd::CommandLine &cmd ) {
	cfg::get()
		.addNode("tool")
		.addNode(name());

	registerProp("tool", "help", 'h', "Display this message", false, cmd, false);
	registerProp("tool", "version", 'v', "Display tool version", version(), cmd, false);
	registerProp("tool", "build", 'b', "Display build information", build(), cmd, false);
	registerProp("tool", "debug", "Set the categories to log with their log level", std::string(""), cmd, false);
	registerProp("tool", "defaults", "Show in xml format the configuration default values", false, cmd, false);
	registerProp("tool", "pretend","Show in xml format the configuration pretend values", false, cmd, false);
	registerProp("tool", "set","Sets the specified configuration values", std::string(""), cmd, false);
}

void Tool::registerOpt( cfg::cmd::CommandLine &cmd, const std::string &owner, const std::string &prop, bool visible, char sname ) {
	if (sname) {
		cmd.registerOpt(owner + "." + prop, prop, sname);
	} else {
		cmd.registerOpt(owner + "." + prop, prop);
	}
	if (!visible) {
		cmd.noShowDefault( prop );
	}
}

void Tool::registerConfigs() {
	char *env = getenv ("HOME");
	std::string home;
	if (env) {
		home = env;
		addConfig( home + "/tool.cfg.xml" );
	}
	addConfig( "tool.cfg.xml" );
	if (env) {
		addConfig( home + "/" + name() + ".cfg.xml" );
	}
	addConfig( name() + ".cfg.xml" );
}

int Tool::execute( int argc, char *argv[] ) {
	int exitCode=-1;
	cfg::cmd::CommandLine cmd( argc, argv );

#ifndef NDEBUG
	try {
#endif

		//	Create tree config
		registerProperties( cmd );

		//	Calls the callbacks that initializes the tool's libraries
		util::reg::init();

		//	Register the configuration files that will be loaded
		registerConfigs();

		//	Load configuration from files
		loadConfig();

		//	Parse commandline
		exitCode = cmd.parse() ? execute( cmd ) : -1;

		//	Calls the callbacks that finalizes the tool's libraries
		util::reg::fin();

#ifndef NDEBUG
	} catch (const std::exception &e) {
		printf( "[Tool] Catch exception: %s\n", e.what() );
	} catch (...) {
		printf( "[Tool] Catch unkown exception\n" );
	}
#endif

	return exitCode;
}

int Tool::execute( cfg::cmd::CommandLine &cmd ) {
	if (cmd.isSet("set")) {
		set();
	}
	if (cmd.isSet("debug")) {
		debug();
	}

	if (cmd.isSet("help")) {
		printf("%s allowed options\n%s\n", name().c_str(), cmd.desc().c_str());
	} else if (cmd.isSet("version")) {
		printVersion();
	} else if (cmd.isSet("build")) {
		printBuild();
	} else if (cmd.isSet("pretend")) {
		pretend();
	} else if (cmd.isSet("defaults")) {
		defaults();
	} else {
		setupSignals();

		//	Initialize log system
		util::log::init();

		int result = run( cmd );

		//	Finalize log system
		util::log::fin();

		return result;
	}
	return 0;
}

int Tool::run( cfg::cmd::CommandLine & /*cmd*/) {
	return 0;
}

}

