#ifndef LOG_FILE_INFO_H_
#define LOG_FILE_INFO_H_

// #include "logging.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

#define FILE_MAX_SIZE 10 * 1024

class LogFile {
public:
    LogFile();
    ~LogFile();
    void setFilename(const std::string& s);
    int getFileSize();
    void fileClose();
    void fileWrite(const std::string& s);
private:
    int f_index;
    int f_size;
    std::string f_format;
    std::string f_name;
};

#endif