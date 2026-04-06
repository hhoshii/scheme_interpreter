#include "pair_and_list_functions.h"
#include "environment.h"

std::shared_ptr<Object> ConsFunction::Apply(std::shared_ptr<Object> args) {
    if (!args || !Is<Cell>(args)) {
        throw RuntimeError("invalid syntax for cons");
    }

    auto arg_cell = As<Cell>(args);

    auto second = arg_cell->GetSecond();
    if (!second || !Is<Cell>(second) || As<Cell>(second)->GetSecond()) {
        throw RuntimeError("wrong num of objects in cons");
    }

    auto first_expr = arg_cell->GetFirst();
    auto second_expr = As<Cell>(second)->GetFirst();
    if (first_expr) {
        first_expr = first_expr->Eval();
    }

    if (second_expr) {
        second_expr = second_expr->Eval();
    }

    return std::make_shared<Cell>(first_expr, second_expr);
}

std::shared_ptr<Object> CarFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    if (!cell) {
        throw RuntimeError("invalid argument for the car function");
    }

    auto arg_expr = cell->GetFirst();
    if (!arg_expr) {
        throw RuntimeError("invalid argument for the car function");
    }

    auto evaluated = arg_expr->Eval();
    if (!Is<Cell>(evaluated)) {
        throw RuntimeError("invalid argument for the car function");
    }

    if (evaluated == nullptr) {
        throw RuntimeError("invalid argument for the car function");
    }

    return As<Cell>(evaluated)->GetFirst();
}

std::shared_ptr<Object> CdrFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    if (!cell) {
        throw RuntimeError("invalid argument for the cdr function");
    }

    auto arg_expr = cell->GetFirst();
    if (!arg_expr) {
        throw RuntimeError("invalid argument for the cdr function");
    }

    auto evaluated = arg_expr->Eval();
    if (!Is<Cell>(evaluated)) {
        throw RuntimeError("invalid argument for the cdr function");
    }

    if (evaluated == nullptr) {
        throw RuntimeError("invalid argument for the cdr function");
    }

    return As<Cell>(evaluated)->GetSecond();
}

std::shared_ptr<Object> ListFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    if (!cell) {
        return std::make_shared<EmptyObject>();
    }

    return cell;
}

std::shared_ptr<Object> ListRefFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    if (!cell || !Is<Cell>(cell->GetSecond())) {
        throw RuntimeError("invalid argument for the list-ref function");
    }

    auto ind_object = As<Cell>(cell->GetSecond())->GetFirst();
    size_t ind = As<Number>(ind_object)->GetValue();
    cell = As<Cell>(cell->GetFirst()->Eval());

    while (ind--) {
        if (!Is<Cell>(cell->GetSecond())) {
            throw RuntimeError("segfault");
        }
        cell = As<Cell>(cell->GetSecond());
    }
    return cell->GetFirst()->Eval();
}

std::shared_ptr<Object> ListTailFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    if (!cell || !Is<Cell>(cell->GetSecond())) {
        throw RuntimeError("invalid argument for the list-ref function");
    }

    auto ind_object = As<Cell>(cell->GetSecond())->GetFirst();
    size_t ind = As<Number>(ind_object)->GetValue();
    cell = As<Cell>(cell->GetFirst()->Eval());

    while (ind--) {
        if (!Is<Cell>(cell->GetSecond())) {
            if (!cell->GetSecond() && !ind) {
                return std::make_shared<EmptyObject>();
            }

            throw RuntimeError("segfault");
        }
        cell = As<Cell>(cell->GetSecond());
    }
    return cell;
}
