
#include "logging.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <iomanip>


ConditionSet::ConditionSet(int level, int print) : levelset(level), printset(print) {

}

bool ConditionSet::levelValidate(int n) {
    return n <= levelset;
}

int ConditionSet::printValidate() {
    return printset;
}



LogControl::LogControl() : pValidator(nullptr) {
    filesize = 0;
    fileindex = 0;
    msg.clear();
    filename.clear();
    fileformat = ".log";
}

void LogControl::setValidator(IValidator* p) { 
    pValidator = p;
}

void LogControl::logMessage(int level, const std::string& msg, const char* file, const char* func, int line) {
    std::string time;
    getTime(time);
    std::ostringstream oss;

    if (pValidator == nullptr || pValidator->levelValidate(level)) {
        oss << "[" << getLevelChar(level) << "]";
        oss << time << " ";
        oss << file << " ";
        oss << func << " ";
        oss << line << ": ";
        oss << msg << std::endl;

        switch (pValidator->printValidate()) {
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

void LogControl::logFileWrite(const std::string& s) {
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

void LogControl::getTime(std::string& s) {
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

char LogControl::getLevelChar(int n) {
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

