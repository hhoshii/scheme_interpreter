#include "tokenizer.h"

bool SymbolToken::operator==(const SymbolToken& other) const {
    return name == other.name;
}

bool QuoteToken::operator==(const QuoteToken&) const {
    return true;
}

bool DotToken::operator==(const DotToken&) const {
    return true;
}

bool ConstantToken::operator==(const ConstantToken& other) const {
    return value == other.value;
}

bool IsSymbol(int x) {
    return !isspace(x) && x != '(' && x != ')' && x != EOF && x != '\'';
}

Tokenizer::Tokenizer(std::istream* in) : in_(in), is_end_(false) {
    Next();
}

bool Tokenizer::IsEnd() {
    return is_end_;
}

void Tokenizer::Next() {
    auto symb = in_->get();
    if (symb == EOF) {
        is_end_ = true;
        last_token_ = {};
        return;
    }

    while (isspace(symb)) {
        symb = in_->get();
    }

    if (symb == EOF) {
        is_end_ = true;
        last_token_ = {};
        return;
    }

    int sign = 1;

    switch (symb) {
        case '(':
            last_token_ = BracketToken::OPEN;
            return;

        case ')':
            last_token_ = BracketToken::CLOSE;
            return;

        case '\'':
            last_token_ = QuoteToken{};
            return;

        case '.':
            last_token_ = DotToken{};
            return;

        case '+':
            if (!isdigit(in_->peek())) {
                last_token_ = SymbolToken{"+"};
                return;
            } else {
                symb = in_->get();
            }
            break;
        case '-':
            if (!isdigit(in_->peek())) {
                last_token_ = SymbolToken{"-"};
                return;
            } else {
                sign = -1;
                symb = in_->get();
            }

        default:;
    }

    if (isdigit(symb)) {
        int val = 0;
        while (isdigit(symb)) {
            val = (val * 10) + (symb - '0');
            symb = in_->get();
        }

        in_->unget();
        last_token_ = ConstantToken{val * sign};
        return;
    }

    std::string name;
    while (IsSymbol(symb)) {
        name += symb;
        symb = in_->get();
    }

    in_->unget();
    last_token_ = SymbolToken{name};
}

Token Tokenizer::GetToken() {
    return last_token_;
}