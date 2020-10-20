
#include "logging.h"



int main() {

    LogFile* lf;

    while (1) {
        getchar();

        LOG_(lf, LOG_INFO, "status INFO mode");
        LOG_(lf, LOG_WARNING, "Status WARNING mode");
        LOG_(lf, LOG_CRITICAL, "Status CRITICAL mode");
        LOG_(lf, LOG_ERROR, "Status ERROR mode");
        LOG_(lf, LOG_DEBUG, "Status DEBUG mode");

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