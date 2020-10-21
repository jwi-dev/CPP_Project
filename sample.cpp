#include "logging.h"
#include <iostream>
#include <thread>


int main() {

    LogSet logset;
    logset.setLevel(LEVEL_ERROR);
    logset.setPrint(PRINT_ALL);
    logset.setFilesize(3 * 1024);

    Logger::getInstance().setLogConfig(&logset);
    // Logger& loginstance = Logger::getInstance();  // default logset 사용
    
    while (1) {
        fprintf(stdout, "===== Logging is running =====\n");
        LOG(LEVEL_DEBUG, "Print DEBUG message");
        LOG(LEVEL_ERROR, "Print ERROR message");
        LOG(LEVEL_CRITICAL, "Print CRITICAL message");
        LOG(LEVEL_WARNING, "Print WARNING message");
        LOG(LEVEL_INFO, "Print INFO message");
        std::this_thread::sleep_for(std::chrono::duration<int>(1));
    }

}