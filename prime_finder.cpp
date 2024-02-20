#include "prime_finder.h"


template<typename T>
std::vector<T> sieve_of_eratosthenes(const T n) {
    // create array of bools on heap
    const size_t size = n + 1;
    auto *is_prime = new bool[size];
    for (unsigned long i = 0; i < size; ++i) {
        is_prime[i] = true;
    }

    // sieve
    for (T number = 2; number < n; ++number) {
        if (is_prime[number]) {
            for (T multiple = number * number; multiple < n; multiple += number) {
                is_prime[multiple] = false;
            }
        }
    }

    // create vector of primes
    std::vector<T> primes;
    for (T number = 2; number < n; ++number) {
        if (is_prime[number]) {
            primes.push_back(number);
        }
    }

    delete[] is_prime;
    verbose_print(primes);
    return primes;
}

template std::vector<unsigned long> sieve_of_eratosthenes(unsigned long n);

template std::vector<int> sieve_of_eratosthenes(int n);


template<typename T>
bool miller_rabin_test(const T n, const size_t iterations) {
    // edge cases
    if (n < 2 || n == 4) return false;
    if (n <= 3) return true;

    // find reduction
    T reduction = n - 1; // n - 1 = 2^s * d
    while (reduction % 2 == 0) { // while d is even
        reduction /= 2; // divide by 2
    }

    // test for iterations
    bool is_prime = true;
    // iterate multiple times
    for (size_t it = 0; it < iterations; ++it) {
        T rand_number = 2 + rand() % (n - 4); // random number from 2 to n - 2
        T x = miller_rabin_computation(rand_number, reduction, n);

        // decide if number is prime or not
        if (x != 1 && x != n - 1) {
            while (reduction != n - 1) {
                x = x * x % n; // x = x^2 mod n
                reduction = reduction * 2;
                if (x == 1) { // if x = 1 then number is not prime
                    is_prime = false;
                    break;
                }
                if (x == n - 1) { // if x = n - 1 then number is probably prime
                    break;
                }
            }
            if (x != n - 1) {  // if x != n - 1 then number is not prime
                is_prime = false;
            }
            if (is_prime == false) {  // if number is not prime then break
                break;
            }
        }
    }
    return is_prime;
}

template bool miller_rabin_test(unsigned long n, size_t iterations);

template bool miller_rabin_test(int n, size_t iterations);


template<typename T>
T miller_rabin_computation(T rand_number, T reduction, const T n) {
    int x = 1;
    while (reduction > 0) {
        if (reduction % 2 == 1) {
            x = x * rand_number % n;
        }
        reduction = reduction / 2;
        rand_number = rand_number * rand_number % n;
    }
    return x;
}

template unsigned long miller_rabin_computation(unsigned long rand_number, unsigned long reduction, unsigned long n);

template int miller_rabin_computation(int rand_number, int reduction, int n);


template<typename T>
std::vector<T> miller_rabin(const T n, const size_t iterations) {
    std::vector<T> primes;
    // do test for all numbers from start_point to n
    for (T i = 0; i < n; ++i) {
        if (miller_rabin_test(i, iterations)) {
            primes.push_back(i);
        }
    }
    verbose_print(primes);
    return primes;
}

template std::vector<unsigned long> miller_rabin(unsigned long n, size_t iterations);

template std::vector<int> miller_rabin(int n, size_t iterations);
