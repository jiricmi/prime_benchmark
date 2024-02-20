// This file is for testing

#include "test_decompose.h"


times *measure_algs(const unsigned long number) {
    // measure standard
    auto start = std::chrono::high_resolution_clock::now();
    const std::vector<unsigned long> primes = sieve_of_eratosthenes(number + 1);
    std::vector<unsigned long> factors = decompose_standard(number, primes);
    auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration_standard = std::chrono::duration_cast<
        std::chrono::microseconds>(end - start);

    // measure pollard
    start = std::chrono::high_resolution_clock::now();
    std::vector<unsigned long> factors2 = decompose_pollard(number);

    // get max from factors by using max_element
    const unsigned long max = *std::max_element(factors2.begin(), factors2.end());

    // fix pollard
    const std::vector<unsigned long> primes2 = sieve_of_eratosthenes(max + 1);
    factors2 = fix_pollard(factors2, primes2);
    end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration_pollard = std::chrono::duration_cast<
        std::chrono::microseconds>(end - start);

    // sort factors
    std::sort(factors.begin(), factors.end());
    std::sort(factors2.begin(), factors2.end());
    auto *data = new times;
    data->number = number;
    data->standard = duration_standard.count();
    data->pollard = duration_pollard.count();
    data->non_error = factors == factors2;
    if (factors != factors2) {
        std::cerr << "Error: " << number << std::endl;
        std::cerr << "Standard: ";
        for (const auto &f: factors) {
            std::cerr << f << " ";
        }
        std::cerr << "Pollard: ";
        for (const auto &f: factors2) {
            std::cerr << f << " ";
        }
    }
    return data;
}


int main() {
    // generate random number
    std::random_device rd;
    std::mt19937 gen(rd());

    const unsigned long intervals[] = {
        10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000,
        1000000, 5000000, 10000000, 50000000, 100000000
    };
    size_t error_counter = 0;
    for (size_t i = 0; i < 14; ++i) {
        std::vector<double> times_standard;
        std::vector<double> times_pollard;
        for (size_t j = 0; j < 100; ++j) {
            const unsigned long number = std::uniform_int_distribution<unsigned long>(intervals[i],
                intervals[i + 1])(gen);

            const auto *ret = measure_algs(number);
            if (!ret->non_error) {
                error_counter++;
            }
            times_standard.push_back(ret->standard);
            times_pollard.push_back(ret->pollard);
            delete ret;
        }
        std::cout << "| " << intervals[i + 1] << " | " << average(times_standard)
                << " | " << average(times_pollard) << " | " << std::endl;
    }
    std::cout << "Errors: " << error_counter << std::endl;
}
