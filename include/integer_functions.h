#pragma once
#include <functions.h>
#include <object.h>

class AddFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class MinusFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class MulFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class DivFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class MaxFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class MinFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class AbsFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};