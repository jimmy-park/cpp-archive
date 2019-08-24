#include "log.h"

constexpr unsigned long long howmany = 1000000;

using namespace std;
using namespace std::chrono;
using std::chrono::high_resolution_clock;

int main()
{
    LOG_LEVEL(LogLevel::kInfo);
    LOG_PATH("");

    auto start = high_resolution_clock::now();
    for (unsigned long long i = 0; i < howmany; i++)
        LOG_INFO(i);
    auto delta = high_resolution_clock::now() - start;
    auto delta_d = duration_cast<duration<double>>(delta).count();

    cout << delta_d << " sec " << int(howmany / delta_d) << " msg/sec" << endl;
}