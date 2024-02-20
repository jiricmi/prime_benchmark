#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>


/**
 * @brief Print message if VERBOSE is defined during compilation
 * @param message Message to be printed
 */
void verbose_print(const std::string &message);


/**
 * @brief Print message if VERBOSE is defined during compilation
 * @param message Message to be printed
 */
template<typename T>
void verbose_print(std::vector<T> &message);


/**
 * @brief Print elapsed time if VERBOSE is defined during compilation
 * @param start_time Start time
 * @param stop_time Stop time
 */
void verbose_time(const std::chrono::high_resolution_clock::time_point &start_time,
                  const std::chrono::high_resolution_clock::time_point &stop_time);


/**
 * @brief Compute average of vector
 * @param v vector
 * @return average of vector
 */
template<typename T>
double average(const std::vector<T> &v);


/**
 * @brief compute gcd of two numbers
 * @ param a first number
 * @ param b second number
 * @ return gcd of a and b
 */
template<typename A, typename B>
unsigned long gcd(A a, B b);


/**
 * @brief check if element is in vector
 * @param v vector
 * @param element element to be checked
 * @return true if element is in vector, false otherwise
 */
template<typename T>
bool is_in_vector(std::vector<T> v, T element);


/**
 * @brief open file and read it to vector
 * @param path path to file
 * @return vector of numbers
 */
std::vector<unsigned long> file_to_vector(const std::string &path);


/**
 * @brief open file check if it is opened and return ifstream
 * @param path path to file
 * @return ifstream
 */
std::ifstream open_read_file(const std::string &path);


/**
 * @brief open file check if it is opened and return ofstream
 * @param path path to file
 * @return ofstream
 */
std::ofstream open_write_file(const std::string &path);


/**
 * @brief ask user for input
 * @param question question to be asked
 * @param allowed_answers allowed answers
 * @return answer
 */
char ask_user(const std::string &question, std::vector<char> allowed_answers);


/**
 * @brief ask user for number input
 * @param question question to be asked
 * @return answer
 */
unsigned long ask_for_number(const std::string &question);

#endif //UTILS_H
