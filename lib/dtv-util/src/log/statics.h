#pragma once

#include "const.h"
#include "target.h"
#include <map>
#include <vector>
#include <string>
#include <boost/thread.hpp>

namespace util {
namespace log {

class Message;
class Formatter;

typedef std::map<std::string, LOG_LEVEL_TYPE> Categories;
typedef std::map<std::string, Categories> Groups;

class Statics {
public:
	static void initStatics( LOG_LEVEL_TYPE level );
	static void finStatics();
	static bool _initialized;

	static bool isLogEnabled();

	static bool canLog( LOG_LEVEL_TYPE level, const std::string &group, const std::string &category );
	static void transmitMessage( const Message &m );

	static Formatter *getFormatter();
	static void addTarget( Target *t );
	static void flushMessages();

	static void setLevel( const std::string &group, const std::string &category, const LOG_LEVEL_TYPE level );

private:
	Statics() {}
	~Statics() {}

	static boost::mutex _initializedMutex;

	static int _nTransmitting;
	static boost::mutex _nTransmittingMutex;
	static boost::condition_variable _nTransmittingCond;

	static Groups _groups;
	static std::vector<Target*> _outputs;
	
	static Formatter *_formatter;
	static LOG_LEVEL_TYPE _defaultLevel;
};

}
}
