// Simple Benchmark Class for Measuring Latency
// Running in Browser : https://godbolt.org/z/GQLnL_

#pragma once

#include <chrono>
#include <string>

#define BENCH(scope_name) \
    Bench scope_latency(scope_name)

class Bench {
public:
    Bench(std::string scope_name);
    ~Bench();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    std::string scope_name_;
};