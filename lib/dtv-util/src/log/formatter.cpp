#include "formatter.h"
#include "message.h"
#include "const.h"

namespace util {
namespace log {

Formatter::Formatter() {
	_buffer.reserve(1024 * 8);
}

std::string &Formatter::format( const Message &message ) {
	_buffer.clear();
	if (!message.group().empty()) {
		_buffer.append( "[" );
		_buffer.append( message.group() );
		if (!message.category().empty()) {
			_buffer.append( "::" );
			_buffer.append( message.category() );
		}
		_buffer.append( "] " );
	}
	_buffer.append( errorDescription( message.level()) );
	_buffer.append( message.message() );
	_buffer.append( "\n" );
	return _buffer;
}

const char *Formatter::errorDescription( const LOG_LEVEL_TYPE level ) {
	if ( level == LOG_LEVEL_ERROR ) {
		return "ERROR: ";
	} else if ( level == LOG_LEVEL_WARN ) {
		return "WARNING: ";
	} else if ( level == LOG_LEVEL_DEBUG ) {
		return "DEBUG: ";
	} else if ( level == LOG_LEVEL_TRACE ) {
		return "TRACE: ";
	} else {
		return "";
	}
}

}
}
