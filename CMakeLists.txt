cmake_minimum_required(VERSION 3.17)
project(rngbench_test)

set(CMAKE_CXX_STANDARD 17)

option(BENCHMARK_ENABLE_TESTING "Enable testing of the benchmark library." OFF)

include( FetchContent )
set( FETCHCONTENT_UPDATES_DISCONNECTED ON )
FetchContent_Declare(
        rangesv3 
        GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
        GIT_TAG master
)
FetchContent_MakeAvailable(rangesv3)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.10.x)

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG master) # need master for benchmark::benchmark


FetchContent_MakeAvailable(rangesv3 googletest googlebenchmark)

add_executable(rngbench_test main.cpp )
target_link_libraries( rngbench_test range-v3::range-v3 benchmark::benchmark )
