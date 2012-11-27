#include "message.h"
#include "statics.h"

namespace util {
namespace log {

Message::Message( const LOG_LEVEL_TYPE level, const std::string &group, const std::string &category, const std::string &msg ) {
	_level = level;
	_group = group;
	_category = category;
	_message = msg;
}

LOG_LEVEL_TYPE Message::level() const {
	return _level;
}

std::string Message::group() const {
	return _group;
}

std::string Message::category() const {
	return _category;
}

std::string Message::message() const {
	return _message;
}

}
}
