#include "error.h"

#include "parser.h"
#include "object.h"

std::shared_ptr<Object> Read(Tokenizer* tokenizer) {
    if (tokenizer->IsEnd()) {
        throw SyntaxError("Empty expression");
    }

    Token token = tokenizer->GetToken();
    std::shared_ptr<Object> result;
    std::visit(
        [&](const auto& t) {
            using T = std::decay_t<decltype(t)>;

            if constexpr (std::is_same_v<T, ConstantToken>) {
                result = std::make_shared<Number>(t.value);
                tokenizer->Next();
            } else if constexpr (std::is_same_v<T, BracketToken>) {
                if (t == BracketToken::OPEN) {
                    tokenizer->Next();
                    result = ReadList(tokenizer);
                } else {
                    result = std::make_shared<CloseBracket>();
                    tokenizer->Next();
                }
            } else if constexpr (std::is_same_v<T, SymbolToken>) {
                if (t.name == "#f") {
                    result = std::make_shared<Boolean>(false);
                } else if (t.name == "#t") {
                    result = std::make_shared<Boolean>(true);
                } else {
                    result = std::make_shared<Symbol>(t.name);
                }
                tokenizer->Next();
            } else if constexpr (std::is_same_v<T, QuoteToken>) {
                tokenizer->Next();
                auto quoted_expr = Read(tokenizer);
                auto args = std::make_shared<Cell>(quoted_expr, nullptr);
                auto buf = std::make_shared<Cell>(std::make_shared<Symbol>("quote"), args);

                buf->SetQuote();
                result = buf;
            } else if constexpr (std::is_same_v<T, DotToken>) {
                result = std::make_shared<Dot>();
                tokenizer->Next();
            }
        },
        token);
    return result;
}

std::shared_ptr<Object> ReadList(Tokenizer* tokenizer) {
    auto cur = Read(tokenizer);
    if (Is<CloseBracket>(cur)) {
        return nullptr;
    }

    if (cur && !Is<Symbol>(cur) && !Is<Number>(cur) && !Is<Cell>(cur) && !Is<Boolean>(cur)) {
        throw SyntaxError("Invalid syntax for list");
    }

    std::shared_ptr<Cell> result(new Cell());
    result->SetFirst(cur);
    auto cur_cell = result;
    cur = Read(tokenizer);

    while (!Is<CloseBracket>(cur)) {
        if (Is<Dot>(cur)) {
            cur = Read(tokenizer);
            cur_cell->SetSecond(cur);
            cur = Read(tokenizer);
            if (!tokenizer->IsEnd() && !Is<CloseBracket>(cur)) {
                throw SyntaxError("Invalid syntax for list");
            }
            break;
        } else {
            if (cur && !Is<Symbol>(cur) && !Is<Number>(cur) && !Is<Cell>(cur) &&
                !Is<Boolean>(cur)) {
                throw SyntaxError("Invalid syntax for list");
            }
            cur_cell->SetSecond(std::make_shared<Cell>());
            cur_cell = std::dynamic_pointer_cast<Cell>(cur_cell->GetSecond());
            cur_cell->SetFirst(cur);
        }
        cur = Read(tokenizer);
    }

    return result;
}
