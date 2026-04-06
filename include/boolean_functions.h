#pragma once
#include <functions.h>
#include <object.h>

class IsNumberFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class IsSymbolFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class IsPairFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class IsNullFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class IsListFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class BoolFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class IsBoolFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class NotFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class AndFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class OrFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};