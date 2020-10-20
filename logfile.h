#ifndef LOG_FILE_INFO_H_
#define LOG_FILE_INFO_H_

#include "logging.h"

class LogFile {
public:
    LogFile();
    ~LogFile();
    void getFilename(std::string& s);
    int getFileSize() { return f_size; }
    FILE* fileOpen();
    void fileClose();
    void fileWrite(const std::string& s);
private:
    FILE* fp;
    int f_index;
    int f_size;
    std::string f_format;
    int f_open;
};


#endif