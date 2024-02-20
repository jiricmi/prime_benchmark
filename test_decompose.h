#ifndef TEST_DECOMPOSE_H
#define TEST_DECOMPOSE_H
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>
#include "prime_finder.h"
#include "decomposition.h"

/**
 * @brief struct for storing measured times
 */
struct times {
    unsigned long number;
    double standard;
    double pollard;
    bool non_error;
};


/**
 * @brief Measure standard and Pollard's rho algorithm
 * @param number Number to be decomposed
 * @return Struct with measured times
 */
times *measure_algs(unsigned long number);

#endif //TEST_DECOMPOSE_H
