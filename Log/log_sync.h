#pragma once

#include <mutex>

#include "log_base.h"

#define LOG_LEVEL LogSync::GetInstance().SetLevel
#define LOG_PATH LogSync::GetInstance().SetPath

#define LOG(file, line, function, level, message)                                                   \
    do {                                                                                            \
        if (LogSync::GetInstance().IsLevelEnabled(level)) {                                         \
            std::ostringstream message_stream;                                                      \
            message_stream << message;                                                              \
            LogSync::GetInstance().LogPrint({ file, line, function, level, message_stream.str() }); \
        }                                                                                           \
    } while (false)

class LogSync : public LogBase<LogSync> {
public:
    void LogPrint(const LogFormat& log_format)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        std::ostringstream output;
        AppendTimePrefix(output, log_format);
        AppendLevelPrefix(output, log_format);
        AppendFuncPrefix(output, log_format);
        output << log_format.message;

        if (file_.is_open())
            file_ << output.str() << std::endl;
        else
            std::clog << output.str() << std::endl;
    }

private:
    std::mutex mutex_;
};