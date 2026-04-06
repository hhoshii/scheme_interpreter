#pragma once

#include <object.h>
#include <unordered_map>

class Function : public Object {
public:
    virtual std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) = 0;
};

class QuoteFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

std::unordered_map<std::string, std::shared_ptr<Function>>& GetFunction();