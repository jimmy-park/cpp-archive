// Thread-Safe and Type-Safe Singleton Logging Class
// Running in Browser : https://godbolt.org/z/UPj5do
// References : https://github.com/nsnam/ns-3-dev-git/blob/master/src/core/model/log.h

#pragma once

#ifdef _WIN32
#include <windows.h>
#else // Unix
#include <sys/stat.h>
#endif // _WIN32
#include <chrono>
#include <csignal>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Singleton/singleton.h"

#ifdef _WIN32
#define __FILENAME__ (std::strrchr(__FILE__, '\\') ? std::strrchr(__FILE__, '\\') + 1 : __FILE__)
#else // Unix
#define __FILENAME__ (std::strrchr(__FILE__, '/') ? std::strrchr(__FILE__, '/') + 1 : __FILE__)
#endif // _WIN32

#ifndef __PRETTY_FUNCTION__
#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__
#else
#define __PRETTY_FUNCTION__ __func__
#endif // _MSC_VER
#endif // __PRETTY_FUNCTION__

#define LOG_FATAL(message) LOG(__FILENAME__, __LINE__, __PRETTY_FUNCTION__, LogLevel::kFatal, message)
#define LOG_ERROR(message) LOG(__FILENAME__, __LINE__, __PRETTY_FUNCTION__, LogLevel::kError, message)
#define LOG_WARN(message) LOG(__FILENAME__, __LINE__, __PRETTY_FUNCTION__, LogLevel::kWarn, message)
#define LOG_INFO(message) LOG(__FILENAME__, __LINE__, __PRETTY_FUNCTION__, LogLevel::kInfo, message)
#define LOG_DEBUG(message) LOG(__FILENAME__, __LINE__, __PRETTY_FUNCTION__, LogLevel::kDebug, message)

// Forward Declaration
//std::string SignalName(int);
void SignalHandler(int);

enum class LogLevel : uint8_t {
    kNone = 0b00000000,
    kFatal = 0b00000001,
    kError = 0b00000010,
    kWarn = 0b00000100,
    kInfo = 0b00001000,
    kDebug = 0b00010000,

    kLevelError = 0b00000011,
    kLevelWarn = 0b00000111,
    kLevelInfo = 0b00001111,
    kLevelDebug = 0b00011111,
    kLevelAll = 0b00011111,

    kPrefixFunc = 0b00100000,
    kPrefixLevel = 0b01000000,
    kPrefixAll = 0b11100000,

    kAll = kPrefixAll | kLevelAll
};

LogLevel operator&(const LogLevel& lhs, const LogLevel& rhs) { return static_cast<LogLevel>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs)); }
LogLevel operator|(const LogLevel& lhs, const LogLevel& rhs) { return static_cast<LogLevel>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs)); }
LogLevel& operator|=(LogLevel& lhs, const LogLevel& rhs) { return lhs = lhs | rhs, lhs; }

struct LogFormat {
    const char* file;
    const int line;
    const char* function;
    const LogLevel level;
    const std::string message;
};

template <typename T>
class LogBase : public Singleton<T> {
public:
    LogBase()
        : levels_{ LogLevel::kNone }
    {
        std::signal(SIGINT, SignalHandler);
        std::signal(SIGILL, SignalHandler);
        std::signal(SIGFPE, SignalHandler);
        std::signal(SIGSEGV, SignalHandler);
        std::signal(SIGTERM, SignalHandler);
        std::signal(SIGABRT, SignalHandler);
    }
    ~LogBase(){};

    void AppendTimePrefix(std::ostringstream& message_stream)
    {
        const auto now = std::chrono::system_clock::now();
        const auto now_time_t = std::chrono::system_clock::to_time_t(now);
        const auto now_us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;

        message_stream << std::put_time(std::localtime(&now_time_t), "%Y-%m-%d %X") << "." << std::setfill('0') << std::setw(6) << now_us.count() << " ";
    }

    void AppendLevelPrefix(std::ostringstream& message_stream, const LogFormat& log_format)
    {
        switch (log_format.level) {
        case LogLevel::kFatal:
            return (message_stream << "[FATAL] "), void();
        case LogLevel::kError:
            return (message_stream << "[ERROR] "), void();
        case LogLevel::kWarn:
            return (message_stream << "[WARN]  "), void();
        case LogLevel::kInfo:
            return (message_stream << "[INFO]  "), void();
        case LogLevel::kDebug:
            return (message_stream << "[DEBUG] "), void();
        default:
            return (message_stream << "[UNKNOWN] "), void();
        }
    }

    void AppendFuncPrefix(std::ostringstream& message_stream, const LogFormat& log_format)
    {
        if (IsLevelEnabled(LogLevel::kPrefixFunc))
            message_stream << log_format.file << "(" << log_format.line << "):" << log_format.function << " ";
    }

    void SetLevel(const LogLevel& level)
    {
        levels_ |= level;
    }
    void SetPath(const char* path)
    {
        file_.open(path, std::ios::out | std::ios::binary);

        if (!file_.is_open()) {
#ifdef _WIN32
            CreateDirectoryA("log", nullptr);
#elif defined(unix) || defined(__unix__) || defined(__unix)
            mkdir("log", 0777);
#endif // _MSC_VER
            const auto now = std::chrono::system_clock::now();
            const auto now_time_t = std::chrono::system_clock::to_time_t(now);

            std::ostringstream oss;
            oss << "log/" << std::put_time(std::localtime(&now_time_t), "[%y%m%d %a] %H-%M-%S") << ".log";

            const auto str = oss.str();
            file_.open(str.c_str(), std::ios::out | std::ios::binary);
        }
    }

    bool IsLevelEnabled(const LogLevel& level) const { return static_cast<uint8_t>(level & levels_) ? true : false; }

protected:
    LogLevel levels_;
    std::ofstream file_;
};
