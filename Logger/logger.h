#pragma once

#include <memory>
#include <string>

#include "log_config.h"
#include "logger_impl_w.h"
#include "singleton.h"

#define MDSLog mds::Logger::GetInstance().Log

namespace mds {

class Logger : public Singleton<Logger> {
public:
    Logger();
    ~Logger();

    void Initialize();
    void Log();
    std::shared_ptr<LogConfig> GetConfig() { return log_config_; }

private:
    std::unique_ptr<LoggerImplW> impl_;
    std::shared_ptr<LogConfig> log_config_;
};

} // namespace mds
