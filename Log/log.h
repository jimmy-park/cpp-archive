#pragma once

#include <chrono>
#include <cstdint>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <shared_mutex>
#include <sstream>
#include <string>

#include "singleton.h"

#ifdef _MSC_VER
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif // _MSC_VER

#define MDS_LOG(level, msg)                             \
    do {                                                \
        if (Logger::GetInstance().IsEnabled(level)) {   \
            std::ostringstream output;                  \
            MDS_LOG_APPEND_TIME_PREFIX(output);         \
            MDS_LOG_APPEND_FUNC_PREFIX(output);         \
            MDS_LOG_APPEND_LEVEL_PREFIX(output, level); \
            output << msg << "\n";                      \
            std::clog << output.str();                  \
            std::clog.flush();                          \
        }                                               \
    } while (false)

#define MDS_LOG_APPEND_TIME_PREFIX(output) \
    output << "[" << Logger::GetInstance().GetTimestamp() << "] "

#define MDS_LOG_APPEND_FUNC_PREFIX(output)                                                   \
    if (Logger::GetInstance().IsEnabled(LogLevel::kPrefixFunc)) {                            \
        output << "[" << __FILE__ << "(" << __LINE__ << "):" << __PRETTY_FUNCTION__ << "] "; \
    }

#define MDS_LOG_APPEND_LEVEL_PREFIX(output, level) \
    output << "[" << Logger::GetInstance().GetLevelLabel(level) << "] "

#define MDS_LOG_INFO(msg) MDS_LOG(LogLevel::kInfo, msg)
#define MDS_LOG_DEBUG(msg) MDS_LOG(LogLevel::kDebug, msg)
#define MDS_LOG_WARN(msg) MDS_LOG(LogLevel::kWarn, msg)
#define MDS_LOG_ERROR(msg) MDS_LOG(LogLevel::kError, msg)

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

inline LogLevel operator&(const LogLevel& lhs, const LogLevel& rhs)
{
    return static_cast<LogLevel>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}

inline LogLevel operator|(const LogLevel& lhs, const LogLevel& rhs)
{
    return static_cast<LogLevel>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

inline LogLevel& operator|=(LogLevel& lhs, const LogLevel& rhs)
{
    lhs = lhs | rhs;
    return lhs;
}

class Logger : public Singleton<Logger> {
public:
    Logger()
        : levels_(LogLevel::kNone){};
    ~Logger() = default;

    inline std::string GetTimestamp()
    {
        const auto now = std::chrono::system_clock::now();
        const auto now_time_t = std::chrono::system_clock::to_time_t(now);
        const auto now_us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&now_time_t), "%F %T") << "." << std::setfill('0') << std::setw(6) << now_us.count();

        return oss.str();
    }

    inline std::string GetLevelLabel(const LogLevel& level)
    {
        switch (level) {
        case LogLevel::kError:
            return "ERROR";
        case LogLevel::kWarn:
            return "WARN ";
        case LogLevel::kDebug:
            return "DEBUG";
        case LogLevel::kInfo:
            return "INFO ";
        default:
            return "UNKNO";
        }
    }

    inline void Enable(const LogLevel& level) { levels_ |= level; }
    inline bool IsEnabled(const LogLevel& level) const { return static_cast<uint8_t>(level & levels_) ? true : false; }

private:
    LogLevel levels_;
};