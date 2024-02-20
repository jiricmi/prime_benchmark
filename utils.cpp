#include "utils.h"

void verbose_print(const std::string &message) {
#ifdef VERBOSE
    std::cout << "DEBUG LOG: " << message << std::endl;
#endif
    static_cast<void>(message);
}


template<typename T>
void verbose_print(std::vector<T> &message) {
#ifdef VERBOSE
    std::cout << "DEBUG LOG: ";
    for (auto &i: message) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
#endif
    static_cast<void>(message);
}

template void verbose_print(std::vector<unsigned long> &message);

template void verbose_print(std::vector<int> &message);

template void verbose_print(std::vector<double> &message);

template void verbose_print(std::vector<float> &message);


void verbose_time(const std::chrono::high_resolution_clock::time_point &start_time,
                  const std::chrono::high_resolution_clock::time_point &stop_time) {
    const std::chrono::duration<double> elapsed = stop_time - start_time;
    verbose_print("Elapsed time: " + std::to_string(elapsed.count()) + " s");
}


template<typename T>
double average(const std::vector<T> &v) {
    double sum = 0;
    for (auto &i: v) {
        sum += i;
    }
    return sum / static_cast<T>(v.size());
}

template double average(const std::vector<double> &v);

template double average(const std::vector<float> &v);

template double average(const std::vector<int> &v);

template double average(const std::vector<unsigned long> &v);


template<typename A, typename B>
unsigned long gcd(A a, B b) {
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

template unsigned long gcd(unsigned long a, unsigned long b);

template unsigned long gcd(int a, int b);

template unsigned long gcd(int a, unsigned long b);

template unsigned long gcd(unsigned long a, int b);


template<typename T>
bool is_in_vector(std::vector<T> v, T element) {
    // check if element is in vector by splitting vector in half
    if (v.size() == 1) {
        return v[0] == element;
    }
    if (v.size() == 2) {
        return v[0] == element || v[1] == element;
    }

    size_t middle = v.size() / 2;
    if (element < v[middle]) {
        return is_in_vector(std::vector<T>(v.begin(), v.begin() + middle), element);
    } else {
        return is_in_vector(std::vector<T>(v.begin() + middle, v.end()), element);
    }
}

template bool is_in_vector(std::vector<unsigned long> v, unsigned long element);

template bool is_in_vector(std::vector<int> v, int element);


std::vector<unsigned long> file_to_vector(const std::string &path) {
    std::ifstream file = open_read_file(path);
    std::vector<unsigned long> v;
    unsigned long number;
    while (file >> number) {
        v.push_back(number);
    }
    file.close();
    return v;
}


std::ifstream open_read_file(const std::string &path) {
    std::ifstream file;
    file.open(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + path);
    }
    return file;
}


std::ofstream open_write_file(const std::string &path) {
    std::ofstream file;
    file.open(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + path);
    }
    return file;
}


char ask_user(const std::string &question, std::vector<char> allowed_answers) {
    std::cout << question << std::endl;
    while (true) {
        std::string answer;
        std::cin >> answer;
        if (answer.length() != 1) {
            std::cout << "Please enter only one character" << std::endl;
            continue;
        }

        char answer_char = answer[0];
        if (std::find(allowed_answers.begin(), allowed_answers.end(), answer_char) != allowed_answers.end()) {
            return answer_char;
        }
        std::cout << "Please enter one of the following characters: ";
        for (const char c: allowed_answers) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
}


unsigned long ask_for_number(const std::string &question) {
    std::cout << question << std::endl;
    while (true) {
        std::string answer;
        std::cin >> answer;
        try {
            return std::stoul(answer);
        } catch (std::invalid_argument &e) {
            std::cout << "Please enter a number" << std::endl;
        }
    }
}
