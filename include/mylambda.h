#pragma once
#include "functions.h"
#include "environment.h"
class MyLambda : public Function, public std::enable_shared_from_this<MyLambda> {
public:
    MyLambda(std::shared_ptr<Cell> params, std::shared_ptr<Cell> body,
             std::shared_ptr<Environment> env);
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;

private:
    std::shared_ptr<Cell> params_;
    std::shared_ptr<Cell> body_;
    std::shared_ptr<Environment> env_;
};