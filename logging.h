#ifndef _LOGGING_H_
#define _LOGGING_H_

#include <string>

#define MSG_(classname, level, msg) classname.logMessage(level, msg, __FILE__, __func__, __LINE__)

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

struct IValidator { 
    virtual ~IValidator() {}

    virtual bool levelValidate(int n) = 0;
    virtual int printValidate() = 0;
};

class ConditionSet : public IValidator {
    int levelset;
    int printset;
public:
    ConditionSet(int level, int print);

    bool levelValidate(int n) override;
    int printValidate() override;
};

class LogControl {
    int filesize;
    int fileindex;
    std::string msg;
    std::string filename;
    std::string fileformat;
    IValidator* pValidator;

public:
    LogControl();

    void setValidator(IValidator* p);

    void logMessage(int level, const std::string& msg, const char* file, const char* func, int line);
    void logFileWrite(const std::string& s);

    char getLevelChar(int n);
    void getTime(std::string& s);
    
};

#endif