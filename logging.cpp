#include "logging.h"

LogFile logfile;

void dbgPrint(int info, const std::string& msg, const char* file, const char* func, int line) {
    
    char c;
    switch (info) {
    case LOG_INFO:      c = 'I'; break;
    case LOG_WARNING:   c = 'W'; break;
    case LOG_ERROR:     c = 'E'; break;
    case LOG_CRITICAL:  c = 'C'; break;
    case LOG_DEBUG:     c = 'D'; break;
    }
    
    std::string date;
    getDate(date);

    std::ostringstream oss;     // 화면 출력
    oss << "[" << c << "]";
    oss << date << " ";
    oss << file << " ";
    oss << func << " ";
    oss << line << ": ";
    oss << msg << std::endl;
    std::cout << oss.str();

    logfile.fileWrite(oss.str());
}