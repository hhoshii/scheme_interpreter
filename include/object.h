#pragma once

#include <memory>
#include <string>

class Object : public std::enable_shared_from_this<Object> {
public:
    Object();
    virtual std::shared_ptr<Object> Eval();
    virtual std::string Serialize();
    virtual ~Object();
};

class Number : public Object {
public:
    Number(int value = 0);
    int GetValue() const;
    std::shared_ptr<Object> Eval() override;
    std::string Serialize() override;

private:
    int value_ = 0;
};

class Boolean : public Object {
public:
    Boolean(bool value = 0);
    bool GetValue() const;
    std::shared_ptr<Object> Eval() override;
    std::string Serialize() override;

private:
    bool value_ = 0;
};

class Symbol : public Object {
public:
    Symbol(std::string value);
    const std::string& GetName() const;
    std::shared_ptr<Object> Eval() override;
    std::string Serialize() override;

private:
    std::string value_;
};

class Dot : public Object {};

class CloseBracket : public Object {
public:
    std::shared_ptr<Object> Eval() override;
    std::string Serialize() override;
};

class EmptyObject : public Object {
public:
    std::shared_ptr<Object> Eval() override;
    std::string Serialize() override;
};

class Cell : public Object {
public:
    Cell() = default;
    Cell(std::shared_ptr<Object> first, std::shared_ptr<Object> second);
    std::shared_ptr<Object> GetFirst() const;
    std::shared_ptr<Object> GetSecond() const;
    void SetFirst(std::shared_ptr<Object> val);
    void SetSecond(std::shared_ptr<Object> val);
    std::shared_ptr<Object> Eval() override;
    std::string Serialize() override;
    void SetQuote();
    bool IsQuote();

private:
    std::shared_ptr<Object> first_, second_;
    bool is_quote_ = false;
};

///////////////////////////////////////////////////////////////////////////////

// Runtime type checking and conversion.
// This can be helpful: https://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast

template <class T>
std::shared_ptr<T> As(const std::shared_ptr<Object>& obj) {
    auto ptr = std::dynamic_pointer_cast<T>(obj);
    return ptr;
}

template <class T>
bool Is(const std::shared_ptr<Object>& obj) {
    return As<T>(obj) != nullptr;
}
