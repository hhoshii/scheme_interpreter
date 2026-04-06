//
// Created by bulat on 04.12.2025.
//

#include "mylambda.h"

MyLambda::MyLambda(std::shared_ptr<Cell> params, std::shared_ptr<Cell> body,
                   std::shared_ptr<Environment> env)
    : params_(params), body_(body), env_(env) {
}

std::shared_ptr<Object> MyLambda::Apply(std::shared_ptr<Object> args) {
    auto cur_env = std::make_shared<Environment>(env_);
    std::shared_ptr<Object> param_it = params_;
    std::shared_ptr<Object> arg_it = args;
    auto prev = NewEnv(cur_env);

    while (param_it && Is<Cell>(param_it)) {
        auto cell = As<Cell>(param_it);
        auto name = cell->GetFirst();

        if (!arg_it) {
            PrevEnv(prev);
            throw RuntimeError("invalid parametrs for lambda");
        }

        auto value = As<Cell>(arg_it)->GetFirst()->Eval();
        std::string pname = As<Symbol>(name)->GetName();

        cur_env->Define(pname, value);

        param_it = cell->GetSecond();
        arg_it = As<Cell>(arg_it)->GetSecond();
    }

    if (arg_it) {
        PrevEnv(prev);
        throw RuntimeError("wrong number of arguments for lambda");
    }

    std::shared_ptr<Object> result = std::make_shared<Cell>();
    std::shared_ptr<Object> body_it = body_;

    while (body_it) {
        if (!Is<Cell>(body_it)) {
            PrevEnv(prev);
            throw RuntimeError("wrong number of arguments for lambda");
        }

        auto expr = As<Cell>(body_it)->GetFirst();
        if (!expr) {
            PrevEnv(prev);
            return result;
        }

        result = expr->Eval();
        body_it = As<Cell>(body_it)->GetSecond();
    }

    PrevEnv(prev);
    return result;
}
