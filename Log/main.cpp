#include <future>
#include <csignal>

#include "log_sync.h"

void print(const LogLevel& level)
{
    for (int i = 0; i < 1000; ++i) {
        LOG(__FILENAME__, __LINE__, __PRETTY_FUNCTION__, level, i);
    }
}

int main()
{
    LOG_LEVEL(LogLevel::kAll);
    // LOG_LEVEL(LogLevel::kPrefixLevel | LogLevel::kInfo | LogLevel::kError);
    //LOG_PATH("temp.log");

    // auto fut1 = std::async(std::launch::async, print, LogLevel::kInfo);
    // auto fut2 = std::async(std::launch::async, print, LogLevel::kDebug);
    // auto fut3 = std::async(std::launch::async, print, LogLevel::kWarn);
    // auto fut4 = std::async(std::launch::async, print, LogLevel::kError);

    // std::string msg{ "message" };
    // LOG_ERROR("error " << msg);
    // LOG_WARN("warn " << msg);
    // LOG_DEBUG("debug " << msg);
    // LOG_INFO("info " << msg);B
    // fut1.wait();
    // fut2.wait();
    // fut3.wait();
    // fut4.wait();

    std::raise(SIGINT);
    std::raise(SIGILL);
    std::raise(SIGFPE);
    std::raise(SIGSEGV);
    std::raise(SIGTERM);
    std::raise(SIGABRT);
}