#pragma once

#include <chrono>
#include <ctime>
#include <iostream>

#include "log_config.h"

using namespace std;

namespace mds {

class LoggerImplW {
public:
    LoggerImplW(const shared_ptr<LogConfig>& log_config)
        : log_config_(log_config)
    {
        cout << "LoggerImplW ctor" << endl;
        log_config_->type_ = LogType::kBrief;

        cout << "log_config_.use_count() : " << log_config_.use_count() << endl;
    }

    ~LoggerImplW()
    {
        cout << "LoggerImplW dtor" << endl;
        cout << "log_config_.use_count() : " << log_config_.use_count() << endl;
    }

    void Log()
    {
        std::cout << std::endl;
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << std::ctime(&time) << std::endl;
    }

    shared_ptr<LogConfig> log_config_;
};

} // namespace mds