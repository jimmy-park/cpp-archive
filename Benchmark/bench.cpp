#include "bench.h"

#include <iostream>

Bench::Bench(std::string scope_name)
    : start_{ std::chrono::high_resolution_clock::now() }
    , scope_name_{ scope_name }
{
}

Bench::~Bench()
{
    auto elapsed = std::chrono::high_resolution_clock::now() - start_;
    std::cout << '[' << scope_name_ << "] Elapsed Time : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count()
              << " ms" << std::endl;
}