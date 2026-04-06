#include "environment.h"

Environment::Environment(std::shared_ptr<Environment> parent) {
    parent_ = parent;
}

void Environment::Define(std::string s, std::shared_ptr<Object> obj) {
    env_[s] = obj;
}

void Environment::Set(std::string s, std::shared_ptr<Object> obj) {
    std::shared_ptr<Environment> env = shared_from_this();
    while (env) {
        if (env->env_.contains(s)) {
            env->env_[s] = obj;
            return;
        }
        env = env->parent_;
    }

    throw NameError("invalid argument for set");
}

std::shared_ptr<Object> Environment::Get(std::string s) {
    std::shared_ptr<Environment> env = shared_from_this();
    while (env) {
        if (env->env_.contains(s)) {
            return env->env_[s];
        }
        env = env->parent_;
    }

    throw NameError("invalid argument for get var");
}

bool Environment::Check(std::string s) {
    std::shared_ptr<Environment> env = shared_from_this();
    while (env->parent_) {
        if (env->env_.contains(s)) {
            return true;
        }
        env = env->parent_;
    }
    return false;
}

std::shared_ptr<Environment> current_env = nullptr;

std::shared_ptr<Environment> NewEnv(std::shared_ptr<Environment> new_env) {
    std::shared_ptr<Environment> prev = current_env;
    current_env = new_env;
    return prev;
}

void PrevEnv(std::shared_ptr<Environment> prev) {
    current_env = prev;
}
