
#include "logging.h"
#include <iostream>
#include <thread>

int main() {

    LogControl log;
    ConditionSet iset(LEVEL_INFO, PRINT_DISPLAY);

    log.setValidator(&iset);
    
    while (1) {
        MSG_(log, LEVEL_DEBUG, "print debug message");
        MSG_(log, LEVEL_ERROR, "print error message");
        MSG_(log, LEVEL_CRITICAL, "print critical message");
        MSG_(log, LEVEL_WARNING, "print warning message");
        MSG_(log, LEVEL_INFO, "print info message");
        std::this_thread::sleep_for(std::chrono::duration<int>(1));
    }

}