#pragma once
#include <functions.h>
#include <object.h>

class IsEqualFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class IsGreaterFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class IsGreaterOrEqualFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class IsLessOrEqualFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class IsLessFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};