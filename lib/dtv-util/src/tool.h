#pragma once

#include "cfg/cfg.h"
#include "cfg/cmd/commandline.h"
#include <set>
#include <string>

namespace util {

#define CREATE_TOOL(cls,prj) \
	int main(int argc, char *argv[]) { \
		std::string build (prj ## _BUILD_VERSION); \
		std::string tag (prj ## _TAG_VERSION); \
		std::string opts (prj ## _BUILD_OPTS); \
		std::string version(prj ## _VERSION); \
		cls obj(prj ## _NAME, prj ## _DESCRIPTION, version + " (" + tag + ")", "Source: " + tag + '(' + build + ") \nConfig: " + opts ); \
		return obj.execute(argc,argv); \
	} \

class Tool {
public:
	Tool( const std::string &name, const std::string &desc, const std::string &version = "1.0.0", const std::string &build = "0" );
	virtual ~Tool();

	int execute(int argc, char *argv[]);

	const std::string &name() const;
	const std::string &version() const;
	const std::string &description() const;
	const std::string &build() const;

	void pretend() const;
	void defaults() const;

protected:
	virtual int execute( cfg::cmd::CommandLine &cmd );
	virtual int run( cfg::cmd::CommandLine &cmd );

	//	Configuration hook methods
	virtual void setupSignals() const;
	virtual void registerConfigs();
	virtual void registerProperties( cfg::cmd::CommandLine &cmd );

	template<typename T>
	T getCfg( const std::string &property );

	void loadConfig();
	void addConfig( const std::string &xml );

	template<typename T>
	void registerToolProp( const std::string &prop, const char sname, 
			   const std::string &desc, T val, cfg::cmd::CommandLine &cmd, bool visible = true);
	//	Register tool property without a short name
	template<typename T>
	void registerToolProp( const std::string &prop, const std::string &desc,
			       T val, cfg::cmd::CommandLine &cmd, bool visible = true);
	template<typename T>
	void registerProp( const std::string &owner, const std::string &prop, const char sname, 
			   const std::string &desc, T val, cfg::cmd::CommandLine &cmd, bool visible = true);
	template<typename T>
	//	Register property without a short name
	void registerProp( const std::string &owner, const std::string &prop, const std::string &desc,
			   T val, cfg::cmd::CommandLine &cmd, bool visible = true );
	template<typename T>
	void registerCfg( const std::string &owner, const std::string &prop,
			  const std::string &desc, T val, bool visible );
	void registerOpt( cfg::cmd::CommandLine &cmd, const std::string &owner, 
			  const std::string &prop, bool visible, char sname = 0 );

	virtual void printVersion() const;
	virtual void printBuild() const;
	virtual void set() const;
	virtual void debug() const;
	const std::string &makeDescription( std::string &group, std::string &category ) const;

private:
	std::string _name;
	std::string _desc;
	std::string _version;
	std::string _build;
	std::set<std::string> _cfgXmls;

};

template<typename T>
void Tool::registerToolProp( const std::string &prop, const char sname, const std::string &desc, T val, cfg::cmd::CommandLine &cmd, bool visible ) {
	registerProp( "tool." + name(), prop, sname, desc, val, cmd, visible );
}

template<typename T>
void Tool::registerToolProp( const std::string &prop, const std::string &desc, T val, cfg::cmd::CommandLine &cmd, bool visible ) {
	registerProp( "tool." + name(), prop, desc, val, cmd, visible );
}

template<typename T>
void Tool::registerProp( const std::string &owner, const std::string &prop, const char sname, const std::string &desc, T val, cfg::cmd::CommandLine &cmd, bool visible ) {
       registerCfg( owner, prop, desc, val, visible );
       registerOpt(cmd, owner, prop, visible, sname);
}

template<typename T>
void Tool::registerProp( const std::string &owner, const std::string &prop, const std::string &desc, T val, cfg::cmd::CommandLine &cmd, bool visible ) {
	registerCfg(owner, prop, desc, val, visible);
	registerOpt(cmd, owner, prop, visible);
}

template<typename T>
void Tool::registerCfg( const std::string &owner, const std::string &prop, const std::string &desc, T val, bool visible ) { 
	cfg::get(owner).addValue(prop, desc, val);
	if (!visible) {
		cfg::get(owner).makeInvisible(prop);
	}
}

template<typename T>
T Tool::getCfg( const std::string &property ) {
	return cfg::getValue<T> ( "tool." + name() + "." + property );
}

}
