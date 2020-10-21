#ifndef _LOGGING_H_
#define _LOGGING_H_

#include <string>

#define LOG(level, msg) Logger::getInstance().logMessage(level, msg, __FILE__, __func__, __LINE__)

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

    virtual bool levelConfig(int n) = 0;
    virtual int printConfig() = 0;
    virtual int filesizeConfig() = 0;
    virtual const std::string& dirConfig() = 0;
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
    bool levelConfig(int n) override;
    int printConfig() override;
    int filesizeConfig() override;
    const std::string& dirConfig() override;
};

class Logger {
private:
    std::string filename;
    std::string fileformat;
    ILogConfig* config;

    Logger();

    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;

public:
    static Logger& getInstance();

    void setLogConfig(ILogConfig* p);

    void logMessage(int level, const std::string& msg, const char* file, const char* func, int line);
    void logFileWrite(int _level, const std::string& s);
    char getLevelChar(int _level);
    void getTime(std::string& s);
    
};

#endif