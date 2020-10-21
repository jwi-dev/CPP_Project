#ifndef _LOGGING_H_
#define _LOGGING_H_

#include <string>

// #define MSG_(classname, level, msg) classname.logMessage(level, msg, __FILE__, __func__, __LINE__)
#define LOG(level, msg) Logger::getInstance().logMessage(level, msg, __FILE__, __func__, __LINE__)

const int filemaxsize = 3 * 1024;

enum LogLevel {
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_CRITICAL,
    LEVEL_ERROR,
    LEVEL_DEBUG,
};

enum LogPrint {
    PRINT_NONE,
    PRINT_DISPLAY,
    PRINT_FILE,
    PRINT_ALL,
};

struct ILogConfig { 
    virtual ~ILogConfig() {}

    virtual bool levelValidate(int n) = 0;
    virtual int printValidate() = 0;
};

class LogSet : public ILogConfig {
    int levelset;
    int printset;
    int filesizeset;
    std::string dir;
public:
    LogSet();

    void setPrint(int print);
    void setLevel(int level);
    void setFilesize(int size);
    void setDirectory(const std::string& s);
    bool levelValidate(int n) override;
    int printValidate() override;
};

class Logger {
private:
    int filesize;
    int fileindex;
    std::string filename;
    std::string fileformat;
    ILogConfig* config;

    Logger();

    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;

public:
    static Logger& getInstance();

    void setValidator(ILogConfig* p);

    void logMessage(int level, const std::string& msg, const char* file, const char* func, int line);
    void logFileWrite(const std::string& s);
    char getLevelChar(int n);
    void getTime(std::string& s);
    
};

#endif