#ifndef DECOMPOSITION_H
#define DECOMPOSITION_H

#include <vector>
#include <algorithm>
#include "utils.h"


/**
 * @brief Decompose number into prime factors
 * @param number Number to be decomposed
 * @param primes Vector of primes
 * @return Vector of prime factors
 */
template<typename T>
std::vector<T> decompose_standard(T number, std::vector<T> primes);

/**
 * @brief Decompose number into prime factors using Pollard's rho algorithm
 * @param number Number to be decomposed
 * @return Vector of prime factors
 */
template<typename T>
std::vector<T> decompose_pollard_recursive(T number);


/**
 * @brief Decompose number into prime factors using Pollard's rho algorithm
 * @param number Number to be decomposed
 * @return Vector of prime factors
 */
template<typename T>
std::vector<T> decompose_pollard(T number);


/**
 * @brief Fix Pollard's rho algorithm by using standard decomposition
 * @param prime_factors Vector of prime factors
 * @param primes Vector of primes
 * @return Vector of prime factors
 */
template<typename T>
std::vector<T> fix_pollard(std::vector<T> prime_factors, std::vector<T> primes);

#endif //DECOMPOSITION_H
