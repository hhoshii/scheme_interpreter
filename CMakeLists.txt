cmake_minimum_required(VERSION 3.0)
project(scheme_interpreter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files for the library
set(SOURCES
    src/tokenizer.cpp
    src/parser.cpp
    src/scheme.cpp
    src/object.cpp
    src/environment.cpp
    src/functions.cpp
    src/boolean_functions.cpp
    src/comparison_functions.cpp
    src/integer_functions.cpp
    src/pair_and_list_functions.cpp
    src/mylambda.cpp
)

# Create the library
add_library(scheme_lib ${SOURCES})
target_include_directories(scheme_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Test executable (requires Catch2 or similar test framework)
# To use: uncomment if you have Catch2 installed
# find_package(Catch2 REQUIRED)
# add_executable(test_scheme 
#     ${SOURCES}
#     tests/test_tokenizer.cpp
#     tests/test_parser.cpp
# )
# target_link_libraries(test_scheme Catch2::Catch2WithMain)

# REPL executable
add_executable(scheme_repl 
    repl/main.cpp
)
target_link_libraries(scheme_repl scheme_lib)

# Installation
install(TARGETS scheme_repl DESTINATION bin)
