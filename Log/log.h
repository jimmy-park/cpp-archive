// Simple Log Class
// Running in Browser : https://godbolt.org/z/gY1Y3r
// References : https://github.com/nsnam/ns-3-dev-git/blob/master/src/core/model/log.h

#pragma once

#include <chrono>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "singleton.h"

#ifdef _MSC_VER
#include <windows.h>
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif // _MSC_VER

#define LOG_ERROR(msg) LOG(LogLevel::kError, msg)
#define LOG_WARN(msg) LOG(LogLevel::kWarn, msg)
#define LOG_DEBUG(msg) LOG(LogLevel::kDebug, msg)
#define LOG_INFO(msg) LOG(LogLevel::kInfo, msg)

#define LOG(level, msg)                                    \
    do {                                                   \
        if (Logger::GetInstance().IsLevelEnabled(level)) { \
            std::ostringstream output;                     \
            LOG_APPEND_TIME_PREFIX(output);                \
            LOG_APPEND_FUNC_PREFIX(output);                \
            LOG_APPEND_LEVEL_PREFIX(output, level);        \
            LOG_APPEND_MESSAGE(output, msg);               \
            LOG_PRINT(output);                             \
        }                                                  \
    } while (false)

#define LOG_APPEND_TIME_PREFIX(output) \
    output << "[" << Logger::GetInstance().GetTimestamp() << "] "

#define LOG_APPEND_FUNC_PREFIX(output)                                                       \
    if (Logger::GetInstance().IsLevelEnabled(LogLevel::kPrefixFunc)) {                       \
        output << "[" << __FILE__ << "(" << __LINE__ << "):" << __PRETTY_FUNCTION__ << "] "; \
    }

#define LOG_APPEND_LEVEL_PREFIX(output, level) \
    output << "[" << Logger::GetInstance().GetLevelLabel(level) << "] "

#define LOG_APPEND_MESSAGE(output, msg) \
    output << msg << "\n";

#define LOG_PRINT(output) \
    Logger::GetInstance().Print(output.str())

#define LOG_LEVEL Logger::GetInstance().SetLevel
#define LOG_PATH Logger::GetInstance().SetPath

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
        : levels_(LogLevel::kNone)
        , file_(){};
    ~Logger(){};

    inline std::string GetTimestamp()
    {
        const auto now = std::chrono::system_clock::now();
        const auto now_time_t = std::chrono::system_clock::to_time_t(now);
        const auto now_us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&now_time_t), "%F %a %T") << "." << std::setfill('0') << std::setw(6) << now_us.count();

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
            return "UNKNOWN";
        }
    }

    inline void SetLevel(const LogLevel& level) { levels_ |= level; }
    inline void SetPath(const char* path)
    {
        file_.open(path, std::ios_base::app);

        if (!file_.is_open()) {
#ifdef _MSC_VER
            CreateDirectoryA("log", nullptr);
#endif // _MSC_VER
            const auto now = std::chrono::system_clock::now();
            const auto now_time_t = std::chrono::system_clock::to_time_t(now);

            std::ostringstream oss;
            oss << "log/" << std::put_time(std::localtime(&now_time_t), "[%y%m%d %a] %H-%M-%S") << ".log";

            const auto str = oss.str();
            const auto c_str = str.c_str();

            file_.open(c_str, std::ios_base::out);
        }
    }

    inline bool IsLevelEnabled(const LogLevel& level) const { return static_cast<uint8_t>(level & levels_) ? true : false; }
    inline bool IsPathEnabled() const { return file_.is_open(); }

    inline void Print(std::string output)
    {
        if (Logger::GetInstance().IsPathEnabled()) {
            file_ << output;
            file_.flush();
        } else {
            std::clog << output;
            std::clog.flush();
        }
    }

private:
    LogLevel levels_;
    std::ofstream file_;
};