#pragma once
// #define SCHEME_FUZZING_2_PRINT_REQUESTS
#include <string>
#include <parser.h>
#include <sstream>

class Interpreter {
public:
    Interpreter();
    std::string Run(const std::string& s);
};
