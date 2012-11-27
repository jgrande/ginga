#pragma once

#include "const.h"
#include <string>

namespace util {
namespace log {

class Message;

class Formatter {
public:
	Formatter();
	virtual ~Formatter() {}

	virtual std::string &format( const Message &message );

protected:
	virtual const char *errorDescription( const LOG_LEVEL_TYPE level );

	std::string _buffer;
};

}
}
