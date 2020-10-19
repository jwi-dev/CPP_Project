#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdio.h>


#define LOG_(info, msg) dbgPrint(info, msg, __FILE__, __func__, __LINE__)

enum log_level {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL,
    LOG_DEBUG,
};

void getDate(std::string& s) {
    std::time_t t = std::time(nullptr);
    std::tm* time_ptr = std::localtime(&t);

    std::stringstream oss;
    oss << "[";
    oss << time_ptr->tm_year + 1900 << "-";
    oss << std::setw(2) << time_ptr->tm_mon << "-";
    oss << std::setw(2) << time_ptr->tm_mday << ", ";
    oss << std::setw(2) << time_ptr->tm_hour << ":";
    oss << std::setw(2) << time_ptr->tm_min << ":";
    oss << std::setw(2) << time_ptr->tm_sec << "]";

    s = oss.str();
}

void dbgPrint(int info, const std::string& msg, const char* file, const char* func, int line) {
    std::string date;
    getDate(date);

    std::cout << "[" << info << "]" << date << " " << file << " " << func << " " << line << ": " << msg << std::endl;
}

int main() {

    while (1) {
        getchar();

        LOG_(LOG_INFO, "INFO");
    }
}

#if 0
struct ILogPrint {
    virtual void Print() = 0;
    virtual ~ILogPrint() {}
};

class PrintFile : public ILogPrint {

public:
    void Print() {

    }
};

class PrintDisplay : public ILogPrint {

public:
    void Print() {

    }
};

class Logger {
public:
    void dbgPrint(ILogPrint* p) { p->Print(); }
};

int main() {
    Logger log;
    PrintFile pf;
    PrintDisplay pd;

    log.dbgPrint(&pf);
    log.dbgPrint(&pd);
}
#endif