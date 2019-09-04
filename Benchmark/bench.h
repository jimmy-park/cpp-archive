// Simple Benchmark Class for Measuring Latency
// Running in Browser : https://godbolt.org/z/GQLnL_

#pragma once

#include <chrono>
#include <string>

#define BENCH(func_name) \
    Bench func_latency(func_name)

class Bench {
public:
    Bench(const char* func_name);
    ~Bench();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    std::string func_name_;
};