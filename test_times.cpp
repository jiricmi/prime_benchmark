// this file is for testing the time complexity of the algorithms
#include "test_times.h"

#define ITERATIONS 1
#define MAX_NUMBER 1000000

int main() {
    const unsigned long intervals[] = {
        10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000,
        1000000, 5000000, 10000000, 50000000, 100000000
    };

    for (unsigned long number: intervals) {
        const double standard = measure_time(ITERATIONS, sieve_of_eratosthenes<unsigned long>, number);
        const double pollard3 = measure_time(ITERATIONS, miller_rabin<unsigned long>, number, 3);
        const double pollard_parallel = measure_time(ITERATIONS, miller_rabin_parallel<unsigned long>,
                                                     number, 3);
        std::cout << "| " << number << "| " << standard << " | " << pollard3 << " | " << pollard_parallel << " |" <<
                std::endl;
    }


    return 0;
}

template<typename Func, typename... Args>
double measure_time(const size_t iterations, Func func, Args &&... args) {
    std::vector<double> times;
    for (size_t i = 0; i < iterations; ++i) {
        // measure time
        const auto start = std::chrono::high_resolution_clock::now();
        func(std::forward<Args>(args)...);
        const auto end = std::chrono::high_resolution_clock::now();

        const std::chrono::duration<double> duration_standard = std::chrono::duration_cast<
            std::chrono::microseconds>(end - start);
        times.push_back(duration_standard.count());
    }
    // compute average time
    return average(times);
}
