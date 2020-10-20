
#include "logfile.h"

LogFile::LogFile() {
    FILE* fp = nullptr;
    f_index = 0;
    f_size = 0;
    f_format = ".log";
    f_open = 0;

    fp = fileOpen();
}

LogFile::~LogFile() {
    fileClose();
}

void LogFile::getFilename(std::string& s) {
    std::time_t t = std::time(nullptr);
    std::tm* time_ptr = std::localtime(&t);

    std::stringstream oss;
    oss << "[";
    oss << time_ptr->tm_year + 1900 << "-";
    oss << std::setw(2) << time_ptr->tm_mon << "-";
    oss << std::setw(2) << time_ptr->tm_mday << ", ";
    oss << std::setw(2) << time_ptr->tm_hour << "]";
    oss << f_format;

    s = oss.str();
}

FILE* LogFile::fileOpen() {
    if (!f_open) {
        std::string filename;
        getFilename(filename);

        FILE* fp = fopen(filename.c_str(), "a");
    }
    return fp;
}

void LogFile::fileClose() {

    if (!fclose(fp)) {
        fp = nullptr;
    }
    else {
        printf("File close error");
    }
}

void LogFile::fileWrite(const std::string& s) {
    fprintf(fp, "%s", s.c_str());
}



