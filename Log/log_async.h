#pragma once

#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "log_base.h"

#define LOG_LEVEL LogAsync::GetInstance().SetLevel
#define LOG_PATH LogAsync::GetInstance().SetPath

#define LOG(file, line, function, level, message)                                                             \
    do {                                                                                                      \
        if (LogAsync::GetInstance().IsLevelEnabled(level)) {                                                  \
            std::ostringstream message_stream;                                                                \
            message_stream << message;                                                                        \
            LogAsync::GetInstance().LogPush({ file, line, function, level, message_stream.str() }); \
        }                                                                                                     \
    } while (false)

class LogAsync : public Singleton<LogAsync>, public LogBase<LogAsync> {
public:
    LogAsync()
        : release_{ false }
        , worker_thread_{ std::thread(&LogAsync::LogFlush, this) }
    {
    }

    ~LogAsync()
    {
        release_ = true;
        worker_thread_.join();
    }

    void LogFlush()
    {
        while (!release_) {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(100ms);

            while (!queue_.empty())
                LogPop();
        }
    }

    void LogPop()
    {
        std::lock_guard<std::mutex> lock(mutex_);

        if (file_.is_open()) {
            file_ << queue_.front() << std::endl;
        } else {
            std::clog << queue_.front() << std::endl;
        }

        queue_.pop();
    }

    void LogPush(const LogFormat& log_format)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        std::ostringstream output;
        AppendTimePrefix(output, log_format);
        AppendLevelPrefix(output, log_format);
        AppendFuncPrefix(output, log_format);
        output << log_format.message;

        queue_.push(output.str());
    }

private:
    bool release_;
    std::mutex mutex_;
    std::queue<std::string> queue_;
    std::thread worker_thread_;
};