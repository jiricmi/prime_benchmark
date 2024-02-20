#include "argument_parser.h"


void no_args() {
    verbose_print("No arguments were passed to the program");
    const char wants_file = ask_user("Do you want to raad from file (f) or console (c)",
                                     {'f', 'c'});

    const char wants_output = ask_user("Do you want to write to file (f) or console (c)",
                                       {'f', 'c'});

    const char method = ask_user("Do you want to use Standard prime factorization (s), "
                                 "Pollard's rho (p) or Pollard's rho with fixing by standard "
                                 "factorization (f)", {'s', 'p', 'f'});
    parse_no_args(wants_file, wants_output, method);
}


int error_message(const std::string &arg) {
    std::cerr << arg << " option requires one argument and only once" << std::endl;
    return 1;
}


int parse_args(const int argc, const char *argv[]) {
    const std::vector<std::string> args(argv + 1, argv + argc);
    const size_t argc_ = args.size();

    char wants_output = 'c';
    char method = 0;
    char prime_method = 0;
    unsigned long k = 0;
    std::string input_file;
    std::string output_file;

    // help
    if (args[0] == "-h" || args[0] == "--help") {
        std::cout << "Usage: " << argv[0] << " [OPTIONS] [FILE]" << std::endl;
        std::cout << "Decomposes numbers into prime factors" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "You can use interactive mode if you don't pass any arguments" << std::endl;
        std::cout << "-h, --help\t \t show this help message and exit" << std::endl;
        std::cout << "-i, --input\t \t input file" << std::endl;
        std::cout << "-o, --output\t output file (without this argument, program will pass output to the console)"
                << std::endl;
        std::cout << "=====================================" << std::endl;
        std::cout << "-m, --method\t method to be used" << std::endl;
        std::cout << "\t \t s - Standard prime factorization" << std::endl;
        std::cout << "\t \t p - Pollard's rho" << std::endl;
        std::cout << "\t \t f - Pollard's rho with fixing by standard factorization" << std::endl;
        std::cout << "=====================================" << std::endl;
        std::cout << "-p, --prime\t prime method to be used for method" << std::endl;
        std::cout << "This option is required if method is Standard prime factorization (s) "
                "or Pollard's rho with fixing by standard factorization (f)" << std::endl;
        std::cout << "\t \t s - Sieve of Eratosthenes" << std::endl;
        std::cout << "\t \t m - Miller-Rabin algorithm" << std::endl;
        std::cout << "\t \t p - Miller-Rabin algorithm parallel" << std::endl;
        std::cout << "=====================================" << std::endl;
        std::cout << "-k, --iterations\t number of iterations for Miller-Rabin algorithm" << std::endl;
        std::cout << "This option is required if prime method is Miller-Rabin algorithm (m) "
                "or Miller-Rabin algorithm parallel (p)" << std::endl;
        return 0;
    }

    // parse arguments from command line
    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i] == "-i" || args[i] == "--input") {
            if (i + 1 < argc_ && input_file.empty()) {
                input_file = args[i + 1];
                ++i;
            } else {
                error_message(args[i]);
            }
        } else if (args[i] == "-o" || args[i] == "--output") {
            if (i + 1 < argc_ && output_file.empty()) {
                output_file = args[i + 1];
                wants_output = 'f';
                ++i;
            } else {
                error_message(args[i]);
            }
        } else if (args[i] == "-m" || args[i] == "--method") {
            if (i + 1 < argc_ && method == 0 && args[i + 1].length() == 1) {
                method = args[i + 1][0];
                if (method != 's' && method != 'p' && method != 'f') {
                    std::cerr << "Method must be one of the following: s, p, f" << std::endl;
                    return 1;
                }
                ++i;
            } else {
                error_message(args[i]);
            }
        } else if (args[i] == "-p" || args[i] == "--prime") {
            if (i + 1 < argc_ && prime_method == 0 && args[i + 1].length() == 1) {
                prime_method = args[i + 1][0];
                if (prime_method != 's' && prime_method != 'm' && prime_method != 'p') {
                    std::cerr << "Prime method must be one of the following: s, m, p" << std::endl;
                    return 1;
                }
                ++i;
            } else {
                error_message(args[i]);
            }
        } else if (args[i] == "-k" || args[i] == "--iterations") {
            if (i + 1 < argc_ && k == 0) {
                try {
                    k = std::stoul(args[i + 1]);
                } catch (std::invalid_argument &e) {
                    std::cerr << "Please enter a number" << std::endl;
                    return 1;
                }
                ++i;
            } else {
                error_message(args[i]);
            }
        } else {
            std::cerr << "Unknown argument: " << args[i] << std::endl;
            return 1;
        }
    }
    return check_args(input_file, output_file, wants_output, method, prime_method, k);
}


bool check_correctness(const char method, const char prime_method) {
    if (method != 's' && method != 'p' && method != 'f' && method != 0) {
        std::cerr << "Method must be one of the following: s, p, f" << std::endl;
        return false;
    }
    if (prime_method != 's' && prime_method != 'm' && prime_method != 'p' && prime_method != 0) {
        std::cerr << "Prime method must be one of the following: s, m, p" << std::endl;
        return false;
    }
    return true;
}


int check_args(const std::string &input_file,
               const std::string &output_file,
               const char wants_output,
               const char method,
               const char prime_method,
               const unsigned long k
) {
    if (!check_correctness(method, prime_method)) return 1;

    if (input_file.empty()) {
        std::cerr << "Please enter the input file" << std::endl;
        return 1;
    }

    if (method == 0) {
        std::cerr << "Please enter the method" << std::endl;
        return 1;
    }

    if (prime_method == 0 && (method == 's' || method == 'f')) {
        std::cerr << "Please enter the prime method" << std::endl;
        return 1;
    } else if (method == 'p' && prime_method != 0) {
        std::cerr << "You can't enter the prime method for Pollard rho" << std::endl;
        return 1;
    }

    if ((prime_method == 'm' || prime_method == 'p') && k == 0) {
        std::cerr << "Please enter the number of iterations" << std::endl;
        return 1;
    } else if (prime_method == 's' && k != 0) {
        std::cerr << "You can't enter the number of iterations for Sieve of Eratosthenes" << std::endl;
        return 1;
    }


    std::vector<unsigned long> v = file_to_vector(input_file);
    std::ofstream output_file_stream;
    if (wants_output == 'f') {
        // open output file if user wants to write to file
        output_file_stream = open_write_file(output_file);
    }

    process_numbers(v, method, prime_method, k, wants_output, output_file_stream);
    return 0;
}


void parse_no_args(const char wants_file, const char wants_output, const char method) {
    if (wants_file == 'f') {
        // read from file, put it to vector and process it
        std::cout << "Please enter the path to the file" << std::endl;
        std::string path;
        std::cin >> path;
        const std::vector<unsigned long> v = file_to_vector(path);

        method_run(v, method, wants_output);
    } else {
        // read from console, put it to vector and process it
        std::cout << "Please enter the numbers separated by space" << std::endl;
        std::string numbers;
        std::cin.ignore();
        std::getline(std::cin, numbers);
        std::vector<unsigned long> v;
        std::stringstream ss(numbers);
        unsigned long number;
        while (ss >> number) {
            v.push_back(number);
        }
        method_run(v, method, wants_output);
    }
}


void method_run(const std::vector<unsigned long> &v, const char method, const char wants_output) {
    std::ofstream output_file;
    if (wants_output == 'f') {
        // open output file if user wants to write to file
        std::string output_name;
        std::cout << "Please enter the path to the output file" << std::endl;
        std::cin >> output_name;
        output_file = open_write_file(output_name);
    }

    char prime_method = 0;

    if (method != 'p') {
        // ask for additional arguments if user want to use Pollard's rho fixed by standard or standard method
        prime_method = ask_user("We need to generate primes. Do you want to use Sieve of "
                                "Eratosthenes (s), Miller-Rabin algorithm (m) or his parallel version (p)"
                                , {'s', 'm', 'p'});
    }

    unsigned long k = 0;
    if (prime_method == 'm' || prime_method == 'p') {
        // ask for additional arguments if user wants to use Miller-Rabin algorithm
        k = ask_for_number("Please enter the number of iterations for Miller-Rabin algorithm");
    }

    process_numbers(v, method, prime_method, k, wants_output, output_file);
}


void process_numbers(const std::vector<unsigned long> &v,
                     const char method,
                     const char prime_method,
                     const unsigned long k,
                     const char wants_output,
                     std::ofstream &output_file

) {
    for (const auto i: v) {
        std::vector<unsigned long> factors = prime_factorization(i, k, prime_method, method);

        // output to file or console
        if (wants_output == 'f') {
            for (const auto j: factors) {
                output_file << j << " ";
            }
            output_file << std::endl;
        } else {
            for (const auto j: factors) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }
    if (wants_output == 'f') {
        output_file.close();
    }
}


std::vector<unsigned long> prime_factorization(const unsigned long number,
                                               const unsigned long k,
                                               const char prime_method,
                                               const char method
) {
    // generate primes if needed
    std::vector<unsigned long> primes;
    if (method == 's' || method == 'f') {
        if (prime_method == 's') {
            primes = sieve_of_eratosthenes(number + 1);
        } else if (prime_method == 'm') {
            primes = miller_rabin(number + 1, k);
        } else if (prime_method == 'p') {
            primes = miller_rabin_parallel(number + 1, k);
        }
    }

    // factorize
    std::vector<unsigned long> factors;
    if (method == 's') {
        factors = decompose_standard(number, primes);
    } else if (method == 'f') {
        factors = decompose_pollard(number);
        factors = fix_pollard(factors, primes);
    } else {
        factors = decompose_pollard(number);
    }
    std::sort(factors.begin(), factors.end());
    return factors;
}
