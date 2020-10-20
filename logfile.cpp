
#include "logfile.h"

LogFile::LogFile() {
    f_index = 0;
    f_size = 0;
    f_format = ".log";
    f_name = "";
}

LogFile::~LogFile() {

}

void LogFile::setFilename(const std::string& s) {

    std::string temp = s + std::to_string(f_index) + f_format;

    FILE* fp = fopen(temp.c_str(), "r");
    if (fp == NULL) {
        f_index = 0;
        f_size = 0;
    }
    else {
        fseek(fp, 0, SEEK_END);
        f_size = ftell(fp);
        fclose(fp);
    }

    if (f_size > FILE_MAX_SIZE) {
        f_name = s + std::to_string(++f_index) + f_format;
        f_size = 0;
    }
    else 
        f_name = temp;
}

void LogFile::fileWrite(const std::string& s) {

    FILE* fp = fopen(f_name.c_str(), "a");
    if ( fp != NULL ) 
        fprintf(fp, "%s", s.c_str());
    else
        printf("[DBG] file open error!!\n");
    
    fclose(fp);
}

int LogFile::getFileSize() {
    return f_size;
}