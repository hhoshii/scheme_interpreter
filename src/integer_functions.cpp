#include "integer_functions.h"
#include "error.h"

std::shared_ptr<Object> AddFunction::Apply(std::shared_ptr<Object> args) {
    if (args == nullptr) {
        return std::make_shared<Number>(0);
    }

    auto cell = As<Cell>(args);
    int result = 0;

    while (cell != nullptr) {
        auto expr = cell->GetFirst();
        if (!expr) {
            throw RuntimeError("invalid argument for the add function");
        }

        auto evaluated = expr->Eval();
        if (!Is<Number>(evaluated)) {
            throw RuntimeError("invalid argument for the add function");
        }

        result += As<Number>(evaluated)->GetValue();
        cell = As<Cell>(cell->GetSecond());
    }

    return std::make_shared<Number>(result);
}

std::shared_ptr<Object> MulFunction::Apply(std::shared_ptr<Object> args) {
    if (args == nullptr) {
        return std::make_shared<Number>(1);
    }

    auto cell = As<Cell>(args);

    int result = 1;

    while (cell != nullptr) {
        auto expr = cell->GetFirst();
        if (!expr) {
            throw RuntimeError("something bad");
        }

        auto evaluated = expr->Eval();
        if (!Is<Number>(evaluated)) {
            throw RuntimeError("invalid argument for the mul function");
        }

        result *= As<Number>(evaluated)->GetValue();
        cell = As<Cell>(cell->GetSecond());
    }

    return std::make_shared<Number>(result);
}

std::shared_ptr<Object> MinusFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);

    if (args == nullptr || !cell || !cell->GetFirst()) {
        throw RuntimeError("the null argument in the minus function");
    }

    auto expr = cell->GetFirst()->Eval();

    if (!Is<Number>(expr)) {
        throw RuntimeError("invalid argument for the minus function");
    }

    int result = As<Number>(expr)->GetValue();
    cell = As<Cell>(cell->GetSecond());

    while (cell != nullptr) {
        expr = cell->GetFirst();
        if (!expr) {
            throw RuntimeError("something bad");
        }

        auto evaluated = expr->Eval();
        if (!Is<Number>(evaluated)) {
            throw RuntimeError("invalid argument for the minus function");
        }

        result -= As<Number>(evaluated)->GetValue();
        cell = As<Cell>(cell->GetSecond());
    }

    return std::make_shared<Number>(result);
}

std::shared_ptr<Object> DivFunction::Apply(std::shared_ptr<Object> args) {
    if (args == nullptr) {
        throw RuntimeError("the null argument in the div function");
    }

    auto cell = As<Cell>(args);
    auto expr = cell->GetFirst()->Eval();

    if (!Is<Number>(expr)) {
        throw RuntimeError("invalid argument for the div function");
    }

    int result = As<Number>(expr)->GetValue();
    cell = As<Cell>(cell->GetSecond());

    while (cell != nullptr) {
        expr = cell->GetFirst();
        if (!expr) {
            throw RuntimeError("something bad");
        }
        auto evaluated = expr->Eval();

        if (!Is<Number>(evaluated)) {
            throw RuntimeError("invalid argument for the div function");
        }

        result /= As<Number>(evaluated)->GetValue();
        cell = As<Cell>(cell->GetSecond());
    }

    return std::make_shared<Number>(result);
}

std::shared_ptr<Object> MaxFunction::Apply(std::shared_ptr<Object> args) {
    if (args == nullptr) {
        throw RuntimeError("the null argument in the max function");
    }

    auto cell = As<Cell>(args);
    auto expr = cell->GetFirst()->Eval();

    if (!Is<Number>(expr)) {
        throw RuntimeError("invalid argument for the max function");
    }
    int result = As<Number>(expr)->GetValue();
    cell = As<Cell>(cell->GetSecond());

    while (cell != nullptr) {
        expr = cell->GetFirst()->Eval();
        if (!Is<Number>(expr)) {
            throw RuntimeError("invalid argument for the max function");
        }

        result = std::max(result, As<Number>(expr)->GetValue());
        cell = As<Cell>(cell->GetSecond());
    }

    return std::make_shared<Number>(result);
}

std::shared_ptr<Object> MinFunction::Apply(std::shared_ptr<Object> args) {
    if (args == nullptr) {
        throw RuntimeError("the null argument in the min function");
    }

    auto cell = As<Cell>(args);
    auto expr = cell->GetFirst()->Eval();

    if (!Is<Number>(expr)) {
        throw RuntimeError("invalid argument for the min function");
    }
    int result = As<Number>(expr)->GetValue();
    cell = As<Cell>(cell->GetSecond());

    while (cell != nullptr) {
        expr = cell->GetFirst()->Eval();
        if (!Is<Number>(expr)) {
            throw RuntimeError("invalid argument for the min function");
        }

        result = std::min(result, As<Number>(expr)->GetValue());
        cell = As<Cell>(cell->GetSecond());
    }

    return std::make_shared<Number>(result);
}

std::shared_ptr<Object> AbsFunction::Apply(std::shared_ptr<Object> args) {
    if (args == nullptr) {
        throw RuntimeError("the null argument in the abs function");
    }

    if (Is<Cell>(As<Cell>(args)->GetSecond())) {
        throw RuntimeError("too many argument for the abs function");
    }

    auto cell = As<Cell>(args);
    auto expr = cell->GetFirst()->Eval();

    if (!Is<Number>(expr)) {
        throw RuntimeError("invalid argument for the abs function");
    }

    int result = abs(As<Number>(expr)->GetValue());
    return std::make_shared<Number>(result);
}
