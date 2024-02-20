#include "prime_finder_parallel.h"

// global variables for threads
size_t done = 0;
std::mutex mutex;
std::mutex primes_mutex;


template<typename T>
void miller_rabin_thread(const T n, const size_t iterations, std::vector<T> &primes) {
    while (true) {
        // lock mutex and check if we are completed
        mutex.lock();
        if (done >= static_cast<size_t>(n)) {
            mutex.unlock();
            return;
        }
        // get number to test and increment done for next thread after that unlock mutex
        T number = done;
        done++;
        mutex.unlock();

        // test if number is prime
        const bool is_prime = miller_rabin_test(number, iterations);

        // if number is prime add it to primes vector (lock mutex to avoid race condition)
        if (is_prime) {
            // lock primes_mutex
            primes_mutex.lock();
            primes.push_back(number);
            primes_mutex.unlock();
        }
    }
}


template<typename T>
std::vector<T> miller_rabin_parallel(const T n, const size_t iterations) {
    const unsigned int num_threads = std::thread::hardware_concurrency(); // get number of threads
    std::vector<std::thread> thread_pool;
    std::vector<T> primes;


    // create threads
    for (size_t i = 0; i < num_threads; ++i) {
        thread_pool.emplace_back(miller_rabin_thread<T>, n, iterations, std::ref(primes));
    }

    // join threads
    for (size_t i = 0; i < num_threads; ++i) {
        thread_pool[i].join();
    }
    done = 0;
    std::sort(primes.begin(), primes.end());
    return primes;
}

template std::vector<unsigned long> miller_rabin_parallel(unsigned long n, size_t iterations);

template std::vector<int> miller_rabin_parallel(int n, size_t iterations);
