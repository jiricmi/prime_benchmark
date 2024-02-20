#ifndef TEST_TIMES_H
#define TEST_TIMES_H
#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
#include <tuple>
#include <utility>
#include "prime_finder.h"
#include "utils.h"
#include "prime_finder_parallel.h"


/**
 * @brief Main function
 * @return 0 if successful
 */
int main();


/**
 * @brief Measure time of function
 * @param iterations Number of iterations
 * @param func Function to be measured
 * @param args Arguments of function
 * @return Average time
 */
template<typename Func, typename... Args>
double measure_time(size_t iterations, Func func, Args &&... args);

#endif //TEST_TIMES_H
