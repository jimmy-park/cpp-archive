#include "logger.h"

#include <memory>
#include <string>

#include "log_config.h"
#include "logger_impl_w.h"

using namespace std;

namespace mds {

Logger::Logger()
{
    cout << "Logger ctor" << endl;
    cout << "log_config_.use_count() : " << log_config_.use_count() << endl;
}

Logger::~Logger()
{
    cout << "Logger dtor" << endl;
    cout << "log_config_.use_count() : " << log_config_.use_count() << endl;
}

void Logger::Initialize()
{
    cout << "Logger::Initialize()" << endl;

    log_config_ = make_shared<LogConfig>(LogType::kVerbose, LogLevel::kTrace, "");
    cout << "log_config_.use_count() : " << log_config_.use_count() << endl;

    impl_ = std::make_unique<LoggerImplW>(log_config_);
}

void Logger::Log()
{
    impl_->Log();
}

} // namespace mds

int main()
{
    using namespace mds;

    Logger::GetInstance().Initialize();

    MDSLog();

    if (Logger::GetInstance().GetConfig()->type_ == LogType::kVerbose)
        MDSLog();

    return 0;
}