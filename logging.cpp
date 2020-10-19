#include "logging.h"


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
    std::cout << oss.str() << std::endl;

    std::string filename;
    getFileInfo(filename);

    filename = filename + ".log";

    

    std::ofstream fout;
    fout.open(filename, std::ios::app);
    if(fout.is_open()) {
        fout << oss.str() << std::endl;
    }
    
    fout.close();
}