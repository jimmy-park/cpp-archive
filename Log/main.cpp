#include <future>

#include "log.h"

void print1()
{
    for (int i = 0; i < 100; ++i) {
        MDS_LOG_INFO("info\t" << i);
    }
}

void print2()
{
    for (int i = 0; i < 100; ++i) {
        MDS_LOG_WARN("warn\t" << i);
    }
}

void print3()
{
    for (int i = 0; i < 100; ++i) {
        MDS_LOG_ERROR("error\t" << i);
    }
}

void print4()
{
    for (int i = 0; i < 100; ++i) {
        MDS_LOG_DEBUG("debug\t" << i);
    }
}

int main()
{
    Logger::GetInstance().Enable(LogLevel::kAll);
    //Logger::GetInstance().Enable(LogLevel::kPrefixLevel | LogLevel::kInfo | LogLevel::kError);

    auto fut1 = std::async(std::launch::async, print1);
    auto fut2 = std::async(std::launch::async, print2);
    auto fut3 = std::async(std::launch::async, print3);
    auto fut4 = std::async(std::launch::async, print4);
}
