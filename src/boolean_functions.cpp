#include "boolean_functions.h"
#include "error.h"

std::shared_ptr<Object> IsNumberFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    if (Is<Number>(cell->GetFirst())) {
        return std::make_shared<Boolean>(true);
    }

    return std::make_shared<Boolean>(false);
}

std::shared_ptr<Object> IsSymbolFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    if (Is<Symbol>(cell->GetFirst()->Eval())) {
        return std::make_shared<Boolean>(true);
    }

    return std::make_shared<Boolean>(false);
}

std::shared_ptr<Object> IsPairFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    if (!Is<Cell>(cell->GetFirst())) {
        return std::make_shared<Boolean>(false);
    }
    auto arg = cell->GetFirst();
    if (!Is<Cell>(arg)) {
        return std::make_shared<Boolean>(false);
    }
    auto c = As<Cell>(arg);
    c = As<Cell>(c->Eval());

    if (!c) {
        return std::make_shared<Boolean>(false);
    }

    return std::make_shared<Boolean>(true);
}

std::shared_ptr<Object> IsNullFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    if (!Is<Cell>(cell->GetFirst())) {
        return std::make_shared<Boolean>(false);
    }

    auto arg = cell->GetFirst();
    if (!Is<Cell>(arg)) {
        return std::make_shared<Boolean>(false);
    }

    auto c = As<Cell>(arg);
    c = As<Cell>(c->Eval());
    if (c) {
        return std::make_shared<Boolean>(false);
    }

    return std::make_shared<Boolean>(true);
}

std::shared_ptr<Object> IsListFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    if (!Is<Cell>(cell->GetFirst())) {
        return std::make_shared<Boolean>(false);
    }

    auto cur = As<Cell>(cell->GetFirst())->Eval();
    while (cur != nullptr) {
        if (!Is<Cell>(cur)) {
            return std::make_shared<Boolean>(false);
        }

        cur = As<Cell>(cur)->GetSecond();
    }

    return std::make_shared<Boolean>(true);
}

std::shared_ptr<Object> BoolFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    if (cell != nullptr) {
        if (Is<Boolean>(cell->GetFirst())) {
            if (!As<Boolean>(cell->GetFirst())->GetValue()) {
                return std::make_shared<Boolean>(false);
            }
        }
    } else {
        if (Is<Boolean>(args)) {
            if (!As<Boolean>(args)->GetValue()) {
                return std::make_shared<Boolean>(false);
            }
        }
    }

    return std::make_shared<Boolean>(true);
}

std::shared_ptr<Object> IsBoolFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    if (Is<Boolean>(cell->GetFirst())) {
        return std::make_shared<Boolean>(true);
    }

    return std::make_shared<Boolean>(false);
}

std::shared_ptr<Object> NotFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    if (cell == nullptr || cell->GetSecond() != nullptr) {
        throw RuntimeError("Invalid syntax for call of not function");
    }
    auto boolean = std::make_shared<BoolFunction>()->Apply(cell);

    if (As<Boolean>(boolean)->GetValue()) {
        return std::make_shared<Boolean>(false);
    }

    return std::make_shared<Boolean>(true);
}

std::shared_ptr<Object> AndFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    std::shared_ptr<Object> last = nullptr;
    while (cell != nullptr) {
        auto expr = cell->GetFirst()->Eval();
        auto boolean = std::make_shared<BoolFunction>()->Apply(expr);

        if (!As<Boolean>(boolean)->GetValue()) {
            return std::make_shared<Boolean>(false);
        }

        last = expr;
        cell = As<Cell>(cell->GetSecond());
    }

    if (last == nullptr) {
        return std::make_shared<Boolean>(true);
    }
    return last;
}

std::shared_ptr<Object> OrFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    while (cell != nullptr) {
        auto expr = cell->GetFirst()->Eval();
        auto boolean = std::make_shared<BoolFunction>()->Apply(expr);

        if (As<Boolean>(boolean)->GetValue()) {
            return expr;
        }

        cell = As<Cell>(cell->GetSecond());
    }

    return std::make_shared<Boolean>(false);
}
