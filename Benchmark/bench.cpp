#include "bench.h"

#include "Log/log_sync.h"

Bench::Bench(const char* func_name)
    : func_name_{ func_name }
    , start_{ std::chrono::high_resolution_clock::now() }
{
    LOG_LEVEL(LogLevel::kInfo);
}

Bench::~Bench()
{
    auto elapsed = std::chrono::high_resolution_clock::now() - start_;
    LOG_INFO("[" << func_name_ << "] Elapsed Time : " << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << " ms");
}