#pragma once

#include "types.h"
#include <string>

namespace util {

class Process {
public:
	explicit Process( const std::string &cmd );
	Process( const std::string &cmd, const Params &params );
	Process( const std::string &cmd, const Environment &env );
	Process( const std::string &cmd, const Params &params, const Environment &env );
	virtual ~Process();

	bool run();
	void kill( int msTimeout=0 );

	// Getters
	PROCESS_ID pid() const;
	bool isRunning();

	//	Params
	void parameters( const Params &params );
	void addParam( const std::string &param );
	void clearParams();
	
	//	Environments
	void environment( const std::string &env );
	void addToEnvironment( const std::string &var ); //format "kay=value"
	void addToEnvironment( const std::string &key, const std::string &value );
	void clearEnvironment();

protected:
	bool checkProcess( bool wait );
	char **makeParams() const;
	char **makeEnv() const;
	void freeParams( char **params );

private:
	PROCESS_ID _pid;
	Params _parameters;
	Environment _environment;

	Process() {};
};

}


