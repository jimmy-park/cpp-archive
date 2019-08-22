#include <future>
#include <thread>

#include "log.h"

void print1()
{
    for (int i = 0; i < 100; ++i) {
        MDS_LOG_ERROR("error\t" << i);
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
        MDS_LOG_DEBUG("debug\t" << i);
    }
}

void print4()
{
    for (int i = 0; i < 100; ++i) {
        MDS_LOG_INFO("info\t" << i);
    }
}

int main()
{
    //Logger::GetInstance().Enable(LogLevel::kAll);
    MDS_LOG_LEVEL(LogLevel::kPrefixLevel | LogLevel::kInfo | LogLevel::kError);

    //auto fut1 = std::async(std::launch::async, print1);
    //auto fut2 = std::async(std::launch::async, print2);
    //auto fut3 = std::async(std::launch::async, print3);
    //auto fut4 = std::async(std::launch::async, print4);

    std::thread t1(print1);
    std::thread t2(print2);
    std::thread t3(print3);
    std::thread t4(print4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}
