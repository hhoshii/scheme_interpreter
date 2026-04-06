#pragma once
#include <functions.h>
#include <object.h>

class ConsFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class CarFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class CdrFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class ListFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class ListRefFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};

class ListTailFunction : public Function {
public:
    std::shared_ptr<Object> Apply(std::shared_ptr<Object> args) override;
};
