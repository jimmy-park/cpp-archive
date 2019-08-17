#include "logger_impl_w.h"

#include <chrono>
#include <ctime>
#include <iostream>

namespace mds {

// void LoggerImplW::Log()
// {
//     // auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
//     // std::cout << std::ctime(&time) << std::endl;
// }

void LoggerImplW::Log2()
{
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << std::ctime(&time) << std::endl;
}

} // namespace mds