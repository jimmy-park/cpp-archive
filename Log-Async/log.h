// Thread-Safe and Type-Safe Asynchronous Logging Class
// Running in Browser : https://godbolt.org/z/tk4uzw
// References : https://github.com/nsnam/ns-3-dev-git/blob/master/src/core/model/log.h

#pragma once

#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <future>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>

#include "singleton.h"

#ifdef _MSC_VER
#include <windows.h>
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#define __PRETTY_FUNCTION__ __FUNCSIG__
#else
#include <sys/stat.h>
#endif // _MSC_VER

#define LOG_LEVEL Logger::GetInstance().SetLevel
#define LOG_PATH Logger::GetInstance().SetPath

#define LOG_ERROR(msg) LOG(LogLevel::kError, msg)
#define LOG_WARN(msg) LOG(LogLevel::kWarn, msg)
#define LOG_DEBUG(msg) LOG(LogLevel::kDebug, msg)
#define LOG_INFO(msg) LOG(LogLevel::kInfo, msg)

#define LOG(level, msg)                                                                                        \
    do {                                                                                                       \
        if (Logger::GetInstance().IsLevelEnabled(level)) {                                                     \
            std::ostringstream output;                                                                         \
            output << msg;                                                                                     \
            auto fut = std::async(std::launch::async, &Logger::LogPush, &Logger::GetInstance(), output.str()); \
        }                                                                                                      \
    } while (false)

#define LOG_LOCK \
    std::lock_guard<std::mutex> lock(Logger::GetInstance().GetMutex())

#define LOG_APPEND_TIME_PREFIX(output) \
    output << "[" << Logger::GetInstance().GetTimestamp() << "] "

#define LOG_APPEND_FUNC_PREFIX(output)                                                       \
    if (Logger::GetInstance().IsLevelEnabled(LogLevel::kPrefixFunc)) {                       \
        output << "[" << __FILE__ << "(" << __LINE__ << "):" << __PRETTY_FUNCTION__ << "] "; \
    }

#define LOG_APPEND_LEVEL_PREFIX(output, level) \
    output << Logger::GetInstance().GetLevelLabel(level)

#define LOG_APPEND_MESSAGE(output, msg) \
    output << msg

#define LOG_PRINT(output) \
    Logger::GetInstance().LogPush(output)

enum class LogLevel : uint8_t {
    kNone = 0b00000000,
    kError = 0b00000001,
    kWarn = 0b00000010,
    kDebug = 0b00000100,
    kInfo = 0b00001000,

    kLevelError = 0b00000001,
    kLevelWarn = 0b00000011,
    kLevelDebug = 0b00000111,
    kLevelInfo = 0b00001111,
    kLevelAll = 0b00011111,

    kPrefixFunc = 0b00100000,
    kPrefixLevel = 0b01000000,
    kPrefixAll = 0b11100000,

    kAll = kPrefixAll | kLevelAll
};

inline LogLevel operator&(const LogLevel& lhs, const LogLevel& rhs) { return static_cast<LogLevel>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs)); }
inline LogLevel operator|(const LogLevel& lhs, const LogLevel& rhs) { return static_cast<LogLevel>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs)); }
inline LogLevel& operator|=(LogLevel& lhs, const LogLevel& rhs) { return lhs = lhs | rhs, lhs; }

class Logger : public Singleton<Logger> {
public:
    Logger();
    ~Logger();

    void LogPop();
    void LogPush(std::string output);

    std::string GetTimestamp();
    std::string GetLevelLabel(const LogLevel& level);

    inline void SetLevel(const LogLevel& level) { levels_ |= level; }
    void SetPath(const char* path);

    inline bool IsLevelEnabled(const LogLevel& level) const { return static_cast<uint8_t>(level & levels_) ? true : false; }

private:
    bool release_;
    LogLevel levels_;
    std::mutex mutex_;
    std::ofstream file_;
    std::queue<std::string> queue_;
    std::condition_variable data_cond_;

    std::future<void> fut;
};
