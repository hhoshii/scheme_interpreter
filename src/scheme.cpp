#include "scheme.h"
#include "environment.h"
#include "functions.h"

Interpreter::Interpreter() {
    auto buf = std::make_shared<Environment>(nullptr);
    auto& functions = GetFunction();
    for (const auto& pair : functions) {
        buf->Define(pair.first, pair.second);
    }
    current_env = std::make_shared<Environment>(buf);
}

std::string Interpreter::Run(const std::string& s) {
    std::stringstream ss{s};
    Tokenizer tokenizer{&ss};
    auto ast = Read(&tokenizer);
    if (!ast) {
        return "()";
    }
    ast = ast->Eval();
    if (!ast) {
        return "()";
    }
    return ast->Serialize();
}
