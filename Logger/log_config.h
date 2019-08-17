#pragma once

#include <string>

#define LOG_TRACE mds::LogLevel::kTrace, __FILE__, __FUNCTION__, __LINE__
#define LOG_INFO mds::LogLevel::kInfo, __FILE__, __FUNCTION__, __LINE__
#define LOG_PEER mds::LogLevel::kPeer, __FILE__, __FUNCTION__, __LINE__
#define LOG_P2P mds::LogLevel::kP2P, __FILE__, __FUNCTION__, __LINE__
#define LOG_SERVER mds::LogLevel::kServer, __FILE__, __FUNCTION__, __LINE__
#define LOG_CONTENT mds::LogLevel::kContent, __FILE__, __FUNCTION__, __LINE__
#define LOG_WARNING mds::LogLevel::kWarning, __FILE__, __FUNCTION__, __LINE__
#define LOG_CRITICAL mds::LogLevel::kCritical, __FILE__, __FUNCTION__, __LINE__

namespace mds {

enum class LogType {
    kVerbose,
    kBrief,
    kDebugSend,
    kDebugRecv
};

enum class LogLevel {
    kTrace,
    kInfo,
    kPeer,
    kP2P,
    kServer,
    kContent,
    kWarning,
    kCritical,
};

struct LogConfig {
    LogConfig(const LogType& type, const LogLevel& level, const std::string& filter)
        : type_(type)
        , level_(level)
        , filter_(filter)
    {
    }

    LogType type_;
    LogLevel level_;
    std::string filter_;
};

} // namespace mds