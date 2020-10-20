
#include "logging.h"
#include "logfile.h"
#include <thread>

void foo() {
    LOG_(LOG_WARNING, "foo function is called");
}
void goo() {
    LOG_(LOG_CRITICAL, "Unknow value");
}
void hoo() {
    LOG_(LOG_ERROR, "Function call failed");
}

int main() {

    // int cnt = 100;

    while (1) {
        // getchar();

        LOG_(LOG_INFO, "main function starts");
        foo();
        goo();
        hoo();
        std::this_thread::sleep_for(std::chrono::duration<int>(1));
    }

    LOG_(LOG_DEBUG, "Process closing");
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