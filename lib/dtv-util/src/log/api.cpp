#include "api.h"
#include "statics.h"
#include "message.h"
#include "../string.h"
#include <stdarg.h>
#include <boost/thread/mutex.hpp>

namespace util {
namespace log {

static LOG_LEVEL_TYPE getLevelValue( const std::string &levelstr ) {
	LOG_LEVEL_TYPE level;
	if (levelstr == "none") {
		level = LOG_LEVEL_NONE;
	} else if (levelstr == "error") {
		level = LOG_LEVEL_ERROR;
	} else if (levelstr == "warn") {
		level = LOG_LEVEL_WARN;
	} else if (levelstr == "info") {
		level = LOG_LEVEL_INFO;
	} else if (levelstr == "debug") {
		level = LOG_LEVEL_DEBUG;
	} else if (levelstr == "trace") {
		level = LOG_LEVEL_TRACE;
	} else if (levelstr == "all") {
		level = LOG_LEVEL_ALL;
	} else {
		throw std::runtime_error( "bad log severity name");
	}
	return level;
}

void initialize( const std::string &level ) {
	Statics::initStatics( getLevelValue(level) );
}

void finalize( ) {
	Statics::finStatics();
}

void flushMessages() {
	Statics::flushMessages();
}

void addStdout() {
	Statics::addTarget(new Cout());
}

void addLogFile( const std::string &filename ) {
	Statics::addTarget(new LogFile(filename));
}

void setLevel( const char *group, const char *category, const char *level ) {
	Statics::setLevel( group, category, getLevelValue(level) );
}

bool canLog( LOG_LEVEL_TYPE level, const char *group, const char *category ) {
	return Statics::canLog(level, group, category);
}

void log( LOG_LEVEL_TYPE level, const char *group, const char *category, const char *format, ... ) {
	va_list args;
	va_start(args, format);
	std::string formatedMsg = format_va( format, args );
	va_end( args );

	Message msg(level, group, category, formatedMsg);
	Statics::transmitMessage(msg);
}

}
}
