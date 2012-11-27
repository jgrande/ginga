#pragma once

#include "const.h"
#include <string>

namespace util {
namespace log {

class Message {
public:
	Message( const LOG_LEVEL_TYPE level, const std::string &group, const std::string &category, const std::string &msg);
	virtual ~Message() {}

	LOG_LEVEL_TYPE level() const;
	std::string group() const;
	std::string category() const;
	std::string message() const;

private:
	LOG_LEVEL_TYPE _level;
	std::string _group;
	std::string _category;
	std::string _message;
};

}
}
