#pragma once

#include "log_config.h"

namespace mds {

class LoggerImpl {
public:
    LoggerImpl();
    virtual ~LoggerImpl();

    virtual void SetLogLevel(LogLevel level);
    virtual void SetFilter(const char* filter);
    virtual void SetLogType(LogType type);

    virtual void Log();

protected:
    bool flushing_;
    LogLevel level_;
    char* filter_;
    LogType type_;
};

} // namespace mds