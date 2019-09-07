#include "bench.h"

#include <iostream>

void func()
{
    BENCH("func()");

    for (auto i = 0; i < 1000; ++i)
        std::cout << i << std::endl;
}

int main()
{
    func();
}