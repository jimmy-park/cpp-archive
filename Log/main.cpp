#include "log.h"

int main()
{
    LOG_LEVEL(LogLevel::kAll);
    //LOG_LEVEL(LogLevel::kPrefixLevel | LogLevel::kInfo | LogLevel::kError);
    //LOG_PATH("test.log");

    std::string msg{ "message" };
    LOG_ERROR("error " << msg);
    LOG_WARN("warn " << msg);
    LOG_DEBUG("debug " << msg);
    LOG_INFO("info " << msg);
}
