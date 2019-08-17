#include "logger_impl.h"

#include <iostream>
#include <string>

namespace mds {

LoggerImpl::LoggerImpl()
    : flushing_(true)
    , level_(LogLevel::kTrace)
    , filter_(nullptr)
    , type_(LogType::kVerbose)
{
}

LoggerImpl::~LoggerImpl()
{
    if (filter_) {
        delete filter_;
        filter_ = nullptr;
    }
}

void LoggerImpl::SetLogLevel(LogLevel level)
{
    level_ = level;
}

void LoggerImpl::SetFilter(const char* filter)
{
    if (filter_) {
        delete filter_;
        filter_ = nullptr;
    }
    filter_ = new char[strlen(filter) + 1];
    filter_[strlen(filter)] = '\0';
    memcpy(filter_, filter, strlen(filter));
}

void LoggerImpl::SetLogType(LogType type)
{
    type_ = type;
}

void LoggerImpl::Log()
{
    std::cout << "LoggerIple" << std::endl;
}

} // namespace mds