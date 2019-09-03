#pragma once

#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>
#include <queue>
#include <shared_mutex>
#include <string>
#include <thread>

#include "log_base.h"

#define LOG_LEVEL LogAsync::GetInstance().SetLevel
#define LOG_PATH LogAsync::GetInstance().SetPath

#define LOG(file, line, function, level, message)                                                   \
    do {                                                                                            \
        if (LogAsync::GetInstance().IsLevelEnabled(level)) {                                        \
            std::ostringstream message_stream;                                                      \
            message_stream << message;                                                              \
            LogAsync::GetInstance().LogPush({ file, line, function, level, message_stream.str() }); \
        }                                                                                           \
    } while (false)

class LogAsync : public LogBase<LogAsync> {
public:
    LogAsync()
        : enqueue_{ true }
        , release_{ false }
        , task_{ std::async(std::launch::async, &LogAsync::LogFlush, this) }
    {
    }

    ~LogAsync()
    {
        enqueue_ = false;
        release_ = true;
        task_.wait();
    }

    void LogFlush()
    {
        while (!release_ || !IsEmpty()) {
            LogPop();
        }
    }

    void LogPop()
    {
        std::unique_lock lock(mutex_);

        while (queue_.empty()) {
            data_cond_.wait(lock);
        }

        if (file_.is_open()) {
            file_ << queue_.front() << std::endl;
        } else {
            std::clog << queue_.front() << std::endl;
        }

        queue_.pop();
    }

    void LogPush(const LogFormat& log_format)
    {
        std::unique_lock lock(mutex_);

        if (!enqueue_)
            return;

        std::ostringstream output;
        AppendTimePrefix(output);
        AppendLevelPrefix(output, log_format);
        AppendFuncPrefix(output, log_format);
        output << log_format.message;

        queue_.emplace(output.str());
        data_cond_.notify_one();
    }

    bool IsEmpty()
    {
        std::shared_lock lock(mutex_);
        return queue_.empty();
    }

private:
    std::atomic_bool enqueue_;
    std::atomic_bool release_;
    mutable std::shared_mutex mutex_;
    std::queue<std::string> queue_;
    std::thread worker_thread_;
    std::future<void> task_;
    std::condition_variable_any data_cond_;
};