#ifndef LOGGING_INFO_H_
#define LOGGING_INFO_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "logfile.h"
#include "logtime.h"

extern LogFile logfile;

#define LOG_(info, msg) dbgPrint(info, msg, __FILE__, __func__, __LINE__)

enum log_level {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL,
    LOG_DEBUG,
};

class LogInfo {
public:


private:

};

void dbgPrint(int info, const std::string& msg, const char* file, const char* func, int line);

#endif