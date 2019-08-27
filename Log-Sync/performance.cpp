#include "log.h"

#include <thread>
#include <vector>

constexpr unsigned long long howmany = 1000000;
constexpr auto threads = 10;

using namespace std;
using namespace std::chrono;
using std::chrono::high_resolution_clock;

int main()
{
    LOG_LEVEL(LogLevel::kInfo);
    LOG_PATH("perf.log");

    cout << "**************************************************************" << endl;
    cout << "Single thread, " << howmany << " iterations" << endl;
    cout << "**************************************************************" << endl;

    auto start = high_resolution_clock::now();
    for (unsigned long long i = 0; i < howmany; i++)
        LOG_INFO(i);
    auto delta = high_resolution_clock::now() - start;
    auto delta_d = duration_cast<duration<double>>(delta).count();

    cout << delta_d << " sec " << int(howmany / delta_d) << " msg/sec\n"
         << endl;

    cout << "**************************************************************" << endl;
    cout << threads << " thread, " << howmany << " iterations" << endl;
    cout << "**************************************************************" << endl;

    vector<thread> threads_;

    start = high_resolution_clock::now();
    for (auto n = 0; n < threads; ++n) {
        threads_.emplace_back([]() {
            for (unsigned long long i = 0; i < howmany / threads; i++)
                LOG_INFO(i);
        });
    }

    for (auto& t : threads_) {
        t.join();
    };

    delta = high_resolution_clock::now() - start;
    delta_d = duration_cast<duration<double>>(delta).count();

    cout << delta_d << " sec " << int(howmany / delta_d) << " msg/sec\n"
         << endl;
}