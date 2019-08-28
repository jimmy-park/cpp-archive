// Thread-Safe and Type-Safe Asynchronous Logging Class
// Running in Browser : https://godbolt.org/z/tk4uzw
// References : https://github.com/nsnam/ns-3-dev-git/blob/master/src/core/model/log.h

#pragma once

#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <cstring>
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
#define __FILENAME__ (std::strrchr(__FILE__, '\\') ? std::strrchr(__FILE__, '\\') + 1 : __FILE__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#else
#include <sys/stat.h>
#define __FILENAME__ (std::strrchr(__FILE__, '/') ? std::strrchr(__FILE__, '/') + 1 : __FILE__)
#endif // _MSC_VER

#define LOG_LEVEL Logger::GetInstance().SetLevel
#define LOG_PATH Logger::GetInstance().SetPath

#define LOG_ERROR(message) LOG(__FILENAME__, __LINE__, __PRETTY_FUNCTION__, LogLevel::kError, message)
#define LOG_WARN(message) LOG(__FILENAME__, __LINE__, __PRETTY_FUNCTION__, LogLevel::kWarn, message)
#define LOG_DEBUG(message) LOG(__FILENAME__, __LINE__, __PRETTY_FUNCTION__, LogLevel::kDebug, message)
#define LOG_INFO(message) LOG(__FILENAME__, __LINE__, __PRETTY_FUNCTION__, LogLevel::kInfo, message)

#define LOG(file, line, function, level, message)                                      \
    do {                                                                               \
        if (Logger::GetInstance().IsLevelEnabled(level)) {                             \
            std::ostringstream message_stream;                                         \
            message_stream << message;                                                 \
            LogFormat log_format{ file, line, function, level, message_stream.str() }; \
            Logger::GetInstance().LogPush(log_format);                                 \
        }                                                                              \
    } while (false)

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

struct LogFormat {
    const char* file;
    const int line;
    const char* function;
    const LogLevel level;
    const std::string message;
};

class Logger : public Singleton<Logger> {
public:
    Logger();
    ~Logger();

    void AppendTimePrefix(std::ostringstream& message_stream, const LogFormat& log_format);
    void AppendLevelPrefix(std::ostringstream& message_stream, const LogFormat& log_format);
    void AppendFuncPrefix(std::ostringstream& message_stream, const LogFormat& log_format);

    void LogFlush();
    void LogPop();
    void LogPush(const LogFormat& log_format);

    void SetLevel(const LogLevel& level);
    void SetPath(const char* path);

    inline bool IsLevelEnabled(const LogLevel& level) const { return static_cast<uint8_t>(level & levels_) ? true : false; }

private:
    bool release_;
    LogLevel levels_;
    std::mutex mutex_;
    std::ofstream file_;
    std::queue<std::string> queue_;
    std::condition_variable data_cond_;

    std::thread thd_;
};
