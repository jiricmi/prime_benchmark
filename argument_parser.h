#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "utils.h"
#include "prime_finder.h"
#include "prime_finder_parallel.h"
#include "decomposition.h"


/**
 * @brief This function parses arguments through command line
 */
void no_args();


/**
 * @brief Write error message to stderr and exit program
 * @param arg Argument that caused error
 */
int error_message(std::string &arg);


/**
 * @brief Parse arguments of the program
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return 0 if successful
 */
int parse_args(int argc, const char *argv[]);


/**
 * @brief check if letters in input are valid
 * @param method method to be checked
 * @param prime_method prime method to be checked
 * @return true if successful
 */
bool check_correctness(char method, char prime_method);


/**
 * @brief check args if they has correct format and if they are valid
 * @param input_file input file to be checked
 * @param output_file output file to be checked
 * @param wants_output output to be checked
 * @param method method to be checked
 * @param prime_method prime method to be checked
 * @param k k to be checked
 * @return 0 if successful
 */
int check_args(const std::string &input_file,
               const std::string &output_file,
               char wants_output,
               char method,
               char prime_method,
               unsigned long k
);


/**
 * @brief parse arguments from command line
 * @param wants_file if 'f', input file is expected
 * @param wants_output if 'f', output file is expected
 * @param method method to be used
 */
void parse_no_args(char wants_file, char wants_output, char method);


/**
 * @brief Ask for additional arguments and run method
 * @param v vector of numbers
 * @param method method to be used
 * @param wants_output if 'f', output file is expected
 */
void method_run(const std::vector<unsigned long> &v, char method, char wants_output);


/**
 * @brief Split vector to the numbers and process each number
 * @param v vector of numbers
 * @param method method to be used
 * @param prime_method prime method to be used
 * @param k number of iterations
 * @param wants_output if 'f', output file is expected
 * @param output_file output file
 */
void process_numbers(const std::vector<unsigned long> &v,
                     char method,
                     char prime_method,
                     unsigned long k,
                     char wants_output,
                     std::ofstream &output_file

);


/**
 * @brief By selected method, run the method
 * @param number number to be factorized
 * @param k number of iterations
 * @param prime_method prime method to be used
 * @param method method to be used
 * @return vector of prime factors
 */
std::vector<unsigned long> prime_factorization(unsigned long number,
                                               unsigned long k,
                                               char prime_method,
                                               char method
);

#endif //ARGUMENT_PARSER_H
