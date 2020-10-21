
#include "logging.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdio.h>


LogSet::LogSet() {
    levelset = 0;
    printset = 0;
    filesizeset = 5;
    dir.clear();
}

void LogSet::setPrint(int print) {
    printset = print;
}

void LogSet::setLevel(int level) {
    levelset = level;
}

void LogSet::setFilesize(int size) {
    filesizeset = size;
}

void LogSet::setDirectory(const std::string& s) {
    dir = s;
}

bool LogSet::levelValidate(int n) {
    return n <= levelset;
}

int LogSet::printValidate() {
    return printset;
}

Logger::Logger() : config(nullptr) {
    filesize = 0;
    fileindex = 0;
    filename.clear();
    fileformat = ".log";

    if (config == nullptr) {
        fprintf(stdout, "initialized config\n");
        static LogSet defaultset;
        defaultset.setLevel(LEVEL_INFO);
        defaultset.setPrint(PRINT_DISPLAY);
        defaultset.setDirectory("./");
        defaultset.setFilesize(5);

        setValidator(&defaultset);
    }
}

void Logger::setValidator(ILogConfig* p) { 
    config = p;
}

void Logger::logMessage(int level, const std::string& msg, const char* file, const char* func, int line) {
    std::string time;
    getTime(time);
    std::ostringstream oss;

    if (config == nullptr || config->levelValidate(level)) {
        
        oss << "[" << getLevelChar(level) << "]";
        oss << time << " ";
        oss << file << " ";
        oss << func << " ";
        oss << line << ": ";
        oss << msg << std::endl;

        switch (config->printValidate()) {
        case PRINT_DISPLAY:
            std::cout << oss.str();
            break;

        case PRINT_FILE:
            logFileWrite(oss.str());
            break;

        case PRINT_ALL:
            std::cout << oss.str();
            logFileWrite(oss.str());
            break;

        case PRINT_NONE:
            break;
        }
    }
    
}

void Logger::logFileWrite(const std::string& s) {
    std::ostringstream oss;
    std::string temp;
    oss << filename << std::to_string(fileindex) << fileformat;
    temp = oss.str();
    oss.clear();
    FILE* fp = fopen(temp.c_str(), "r");
    if (fp == nullptr) {
        fileindex = 0;
        filesize = 0;
    } else {
        fseek(fp, 0, SEEK_END);
        filesize = ftell(fp);
        fclose(fp);
    }

    if (filesize > filemaxsize) {
        oss << filename << std::to_string(++fileindex) << fileformat;
        filesize = 0;
        temp = oss.str();
    }
 
    fp = fopen(temp.c_str(), "a");
    if (fp != nullptr)
        fprintf(fp, "%s", s.c_str());
    else
        fprintf(stderr, "Fail to open new file");

    fclose(fp);
}

void Logger::getTime(std::string& s) {
    std::time_t t = std::time(nullptr);
    std::tm* time_ptr = std::localtime(&t);

    std::ostringstream oss1, oss2;

    oss1 << "[";
    oss1 << time_ptr->tm_year + 1900 << "-";
    oss1 << std::setw(2) << time_ptr->tm_mon << "-";
    oss1 << std::setw(2) << time_ptr->tm_mday << ",";
    oss1 << std::setw(2) << time_ptr->tm_hour << "]";

    filename = oss1.str();

    oss2 << "[";
    oss2 << time_ptr->tm_year + 1900 << "-";
    oss2 << std::setw(2) << time_ptr->tm_mon << "-";
    oss2 << std::setw(2) << time_ptr->tm_mday << ",";
    oss2 << std::setw(2) << time_ptr->tm_hour << ":";
    oss2 << std::setw(2) << time_ptr->tm_min << ":";
    oss2 << std::setw(2) << time_ptr->tm_sec << "]";

    s = oss2.str();
}

char Logger::getLevelChar(int n) {
    char c;
    switch (n) {
    case LEVEL_INFO:      c = 'I'; break;
    case LEVEL_WARNING:   c = 'W'; break;
    case LEVEL_ERROR:     c = 'E'; break;
    case LEVEL_CRITICAL:  c = 'C'; break;
    case LEVEL_DEBUG:     c = 'D'; break;
    }
    return c;
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}