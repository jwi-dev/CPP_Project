#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include "logging.h"
#include "logtime.h"
#include "logfile.h"


int main() {

    while (1) {
        getchar();

        LOG_(LOG_INFO, "status INFO mode");
        LOG_(LOG_WARNING, "Status WARNING mode");
        LOG_(LOG_CRITICAL, "Status CRITICAL mode");
        LOG_(LOG_ERROR, "Status ERROR mode");
        LOG_(LOG_DEBUG, "Status DEBUG mode");

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