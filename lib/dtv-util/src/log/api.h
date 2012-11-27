#pragma once

#include "const.h"
#include <string>

#define LOG_PUBLISH( l, g, c, f, ... ) \
	if (util::log::canLog( LOG_LEVEL_##l, g, c )) { \
		util::log::log( LOG_LEVEL_##l, g, c, f, ##__VA_ARGS__ ); \
	}

#define LOG_TRACE( grp, cat, format, ... )	LOG_PUBLISH( TRACE, grp, cat, format, ##__VA_ARGS__ )
#define LOG_DEBUG( grp, cat, format, ... )	LOG_PUBLISH( DEBUG, grp, cat, format, ##__VA_ARGS__ )
#define LOG_INFO( grp, cat, format, ... )	LOG_PUBLISH( INFO, grp, cat, format, ##__VA_ARGS__ )
#define LOG_WARN( grp, cat, format, ... )	LOG_PUBLISH( WARN, grp, cat, format, ##__VA_ARGS__ )
#define LOG_ERROR( grp, cat, format, ... )	LOG_PUBLISH( ERROR, grp, cat, format, ##__VA_ARGS__ )

namespace util {
namespace log {

// Initialize the log library with the default log severity level.
// Must be called only once before using log macros or log function
void initialize( const std::string &level );

// Finalize the log library realeasing all the objects allocated
// No more calls are to log macros or log function are allowed after calling this function
void finalize();

// Signal logger thread to flush all messages and wait for it to complete
void flushMessages();

// Log to standar output
void addStdout();

// Log to file
void addLogFile( const std::string &filename );

// Sets the severity level for a group/category
// LEVELS: none, error, warn, info, debug, trace, all
void setLevel( const char *group, const char *category, const char *level );

// Return true if this category for this group can log with this level
bool canLog( LOG_LEVEL_TYPE level, const char *group, const char *category );

// Log message for this group/category/level
void log( LOG_LEVEL_TYPE level, const char *group, const char *category, const char *format, ... );

}
}
