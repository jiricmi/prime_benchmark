#include "decomposition.h"


template<typename T>
std::vector<T> decompose_standard(T number, std::vector<T> primes) {
    std::vector<T> prime_factors = {};
    if (number == 1) {
        return {1};
    }
    // check if number is divisible by prime number, if yes, divide it and add prime number to prime_factors
    for (auto &prime: primes) {
        while (number % prime == 0) {
            prime_factors.push_back(prime);
            number /= prime;
        }
        if (number == 1) {
            break;
        }
    }

    // if there is no prime factor, number is prime
    if (prime_factors.empty()) {
        prime_factors.push_back(number);
    }

    verbose_print(prime_factors);
    return prime_factors;
}

template std::vector<unsigned long> decompose_standard(unsigned long number, std::vector<unsigned long> primes);

template std::vector<int> decompose_standard(int number, std::vector<int> primes);


template<typename T>
std::vector<T> decompose_pollard_recursive(T number) {

    // g(x) = x^2 + 1 mod number (random function)
    auto g = [](auto a, auto num) -> T {
        return (a * a + 1) % num;
    };

    // setup variables
    T x = 2;
    T y = 2;
    T d = 1;

    std::vector<T> prime_factors = {};
    // find factor
    while (d == 1) {
        x = g(x, number);
        y = g(g(y, number), number);
        d = gcd(abs(x - y), number);
    }
    if (d == number) {
        // mean that we didnt find factor so we return the number itself (for fix pollard function)
        // or number is prime
        prime_factors.push_back(d);
    } else {
        // mean that we found factor so we divide number by it and decompose it recursively
        prime_factors.push_back(d);
        std::vector<T> other_factors = decompose_pollard_recursive(number / d);
        prime_factors.insert(prime_factors.end(), other_factors.begin(), other_factors.end());
    }

    return prime_factors;
}

template std::vector<unsigned long> decompose_pollard_recursive(unsigned long number);

template std::vector<int> decompose_pollard_recursive(int number);


template<typename T>
std::vector<T> decompose_pollard(T number) {
    std::vector<T> prime_factors = decompose_pollard_recursive(number);
    verbose_print(prime_factors);
    return prime_factors;
}

template std::vector<unsigned long> decompose_pollard(unsigned long number);

template std::vector<int> decompose_pollard(int number);


template<typename T>
std::vector<T> fix_pollard(std::vector<T> prime_factors, std::vector<T> primes) {
    size_t i = 0;
    while (i < prime_factors.size()) {
        if (is_in_vector(primes, prime_factors[i])) {
            i++;
        } else {
            // replace non-prime factor with its prime factors
            std::vector<T> factors = decompose_standard(prime_factors[i], primes);
            prime_factors.erase(prime_factors.begin() + i);
            prime_factors.insert(prime_factors.end(), factors.begin(), factors.end());
        }
    }
    return prime_factors;
}

template std::vector<unsigned long> fix_pollard(std::vector<unsigned long> prime_factors,
                                                std::vector<unsigned long> primes);

template std::vector<int> fix_pollard(std::vector<int> prime_factors, std::vector<int> primes);
