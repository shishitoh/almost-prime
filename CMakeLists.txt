cmake_minimum_required(VERSION 3.1)

project(almost-prime, CXX)

set(CMAKE_CXX_STANDARD 20)

set(SRCS main.cpp sieve.cpp merge.cpp)
file(GLOB SRCS ${SRCS} almprm*.cpp)

set(TARGET almprm)

add_executable(${TARGET} ${SRCS})

target_compile_options(${TARGET} PUBLIC
    $<$<CXX_COMPILER_ID:GNU>: -fdiagnostics-color=always -O2 -Wall>
)