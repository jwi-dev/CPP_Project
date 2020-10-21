#ifndef _LOG_SET_H_
#define _LOG_SET_H_

#include <string>


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

#endif