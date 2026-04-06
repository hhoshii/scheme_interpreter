#pragma once
#include <memory>
#include <unordered_map>
#include "error.h"

class Object;

class Environment : public std::enable_shared_from_this<Environment> {
public:
    explicit Environment(std::shared_ptr<Environment> parent = nullptr);
    void Define(std::string s, std::shared_ptr<Object> obj);
    void Set(std::string s, std::shared_ptr<Object> obj);
    std::shared_ptr<Object> Get(std::string s);
    bool Check(std::string s);

private:
    std::unordered_map<std::string, std::shared_ptr<Object>> env_;
    std::shared_ptr<Environment> parent_;
};

extern std::shared_ptr<Environment> current_env;

std::shared_ptr<Environment> NewEnv(std::shared_ptr<Environment> new_env);

void PrevEnv(std::shared_ptr<Environment> prev);
