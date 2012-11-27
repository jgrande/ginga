#pragma once

#include "log/api.h"
#include <string>

#define TO_STR( x ) (#x)
#define TO_STR_IND( x ) TO_STR(x)

#define LTRACE( cat, msg, ... ) LOG_TRACE( TO_STR_IND(PROJECT_NAME), cat, msg, ##__VA_ARGS__ )
#define LDEBUG( cat, msg, ... ) LOG_DEBUG( TO_STR_IND(PROJECT_NAME), cat, msg, ##__VA_ARGS__ )
#define LINFO( cat, msg, ... )  LOG_INFO( TO_STR_IND(PROJECT_NAME), cat, msg, ##__VA_ARGS__ )
#define LWARN( cat, msg, ... )  LOG_WARN( TO_STR_IND(PROJECT_NAME), cat, msg, ##__VA_ARGS__ )
#define LERROR( cat, msg, ... ) LOG_ERROR( TO_STR_IND(PROJECT_NAME), cat, msg, ##__VA_ARGS__ )

namespace util {
namespace log {

void init();
void flush();
void fin();

}
}
