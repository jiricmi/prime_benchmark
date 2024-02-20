//
// Created by jiricmi on 1/12/24.
//

#ifndef PRIME_FINDER_PARALLEL_H
#define PRIME_FINDER_PARALLEL_H

#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include "prime_finder.h"


/**
 * @brief This function is used by thread to find primes
 * @param n upper bound
 * @param iterations number of iterations
 * @param primes vector of primes
 */
template<typename T>
void miller_rabin_thread(T n, size_t iterations, std::vector<T> &primes);


/**
 * @brief This function finds primes in parallel
 * @param n upper bound
 * @param iterations number of iterations
 * @return vector of primes
 */
template<typename T>
std::vector<T> miller_rabin_parallel(T n, size_t iterations);

#endif //PRIME_FINDER_PARALLEL_H
