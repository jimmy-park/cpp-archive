#include <chrono>
#include <iostream>

constexpr unsigned long long count = 1000000000;

int main()
{
    unsigned long long x = 0;
    unsigned long long sum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    for (unsigned long long i = 0; i < count; i++)
        sum += x++;
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "x++ in i++ loop : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns and sum : " << sum << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (unsigned long long i = 0; i < count; i++)
        sum += ++x;
    end = std::chrono::high_resolution_clock::now();

    std::cout << "++x in i++ loop : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (unsigned long long i = 0; i < count; ++i)
        sum += x++;
    end = std::chrono::high_resolution_clock::now();

    std::cout << "x++ in ++i loop : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (unsigned long long i = 0; i < count; ++i)
        sum += ++x;
    end = std::chrono::high_resolution_clock::now();

    std::cout << "++x in ++i loop : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;
}