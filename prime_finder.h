#ifndef PRIME_FINDER_H
#define PRIME_FINDER_H

#include <vector>
#include "utils.h"
#include <cmath>
#include <random>
#include <chrono>

/**
 * @brief Find all primes smaller than n by sieve of Eratosthenes
 * @param n Upper bound
 * @return Vector of primes
 */
template<typename T>
std::vector<T> sieve_of_eratosthenes(T n);


/**
 * @brief Find if number is prime by Miller-Rabin test
 * @param n number to be tested
 * @param iterations number of iterations
 * @return true if number is prime, false otherwise
 */
template<typename T>
bool miller_rabin_test(T n, size_t iterations);


/**
 * @brief Compute Miller-Rabin test and determine if number is not prime for sure
 * @param rand_number random number
 * @param reduction reduction
 * @param n number to be tested
 * @return x
 */
template<typename T>
T miller_rabin_computation(T rand_number, T reduction, T n);


/**
 * @brief Find all primes smaller than n by Miller-Rabin test
 * @param n Upper bound
 * @param iterations number of iterations
 * @return Vector of primes
 */
template<typename T>
std::vector<T> miller_rabin(T n, size_t iterations);

#endif //PRIME_FINDER_H
