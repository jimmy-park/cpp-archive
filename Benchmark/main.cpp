#include "bench.h"

#include <iostream>

void func()
{
    BENCH("func()");

    for (auto i = 0; i < 100; ++i)
        std::cout << i << std::endl;
}

int main()
{
    func();
}