cmake_minimum_required(VERSION 3.5)
project(PrimeNumber)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(PrimeNumber main.cpp
        prime_finder.cpp
        utils.cpp
        decomposition.cpp
        prime_finder_parallel.cpp
        argument_parser.cpp
)

add_executable(PrimeNumberTest
        test_times.cpp
        prime_finder.cpp
        utils.cpp
        decomposition.cpp
        prime_finder_parallel.cpp
        argument_parser.cpp
)

add_executable(PrimeNumberTest2
        test_decompose.cpp
        prime_finder.cpp
        utils.cpp
        decomposition.cpp
        prime_finder_parallel.cpp
        argument_parser.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(PrimeNumber Threads::Threads)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(PrimeNumber PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
    target_compile_options(PrimeNumberTest PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
    target_compile_options(PrimeNumberTest2 PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
endif ()
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(PrimeNumber PRIVATE /W4)
    target_compile_options(PrimeNumberTest PRIVATE /W4)
    target_compile_options(PrimeNumberTest2 PRIVATE /W4)
endif ()