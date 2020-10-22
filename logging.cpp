#include "logging.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdio.h>


Logger::Logger() : config(nullptr) {
    filename.clear();
    fileformat = ".log";

    if (config == nullptr) {
        fprintf(stdout, "initialized config\n");
        static LogSet defaultset;
        defaultset.setLevel(LEVEL_INFO);
        defaultset.setPrint(PRINT_DISPLAY);
        defaultset.setFilesize(5 * 1024);

        setLogConfig(&defaultset);
    }
}

void Logger::setLogConfig(ILogConfig* p) { config = p; }

void Logger::logMessage(int level, const std::string& msg, const char* file, const char* func, int line) {
    std::string time;
    getTime(time);
    std::ostringstream oss;

    if (config == nullptr || config->levelConfig(level)) {
        
        oss << "[" << getLevelChar(level) << "]";
        oss << time << " ";
        oss << file << " ";
        oss << func << " ";
        oss << line << ": ";
        oss << msg << std::endl;

        switch (config->printConfig()) {
        case PRINT_DISPLAY:
            std::cout << oss.str();
            break;

        case PRINT_FILE:
            logFileWrite(level, oss.str());
            break;

        case PRINT_ALL:
            std::cout << oss.str();
            logFileWrite(level, oss.str());
            break;

        case PRINT_NONE:
            break;
        }
    }
}

void Logger::logFileWrite(int _level, const std::string& s) {
    std::ostringstream oss;
    std::string temp;

    oss << "[" << getLevelChar(_level) << "]";
    oss << filename << fileformat;
    temp = oss.str();
    
    FILE* fp = nullptr;
    int index = 0;
    int size = 0;
    oss.str("");
    while (1) {
        oss << std::to_string(index) << temp;
        fp = fopen(oss.str().c_str(), "a");
        oss.str("");

        if (fp == nullptr) {
            perror("open");
            fprintf(stdout, "Fail to open file\n");
            break;
        }
        
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        if ( (size == 0) || (size < config->filesizeConfig()) ) {
            fprintf(fp, "%s", s.c_str());
            fclose(fp);
            break;
        }
        fclose(fp);
        ++index;
    }
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

char Logger::getLevelChar(int _level) {
    char c;
    switch (_level) {
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