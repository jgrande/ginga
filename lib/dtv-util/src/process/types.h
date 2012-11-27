#pragma once

#include <string>
#include <vector>
#include <map>

typedef std::vector<std::string> Params;
typedef std::map<std::string, std::string> Environment;

#ifdef _WIN32
typedef void *HANDLE;
typedef HANDLE PROCESS_ID;
#define INVALID_PROCESS_ID INVALID_HANDLE_VALUE
#define PATH_SEPARATOR ";"
#else
typedef int PROCESS_ID;
#define INVALID_PROCESS_ID -1
#define PATH_SEPARATOR ":"
#endif
