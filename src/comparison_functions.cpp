#include <functional>
#include "comparison_functions.h"
#include "error.h"

std::shared_ptr<Object> CommonBooleanFunction(std::shared_ptr<Object> args,
                                              std::function<bool(int, int)> predicate) {
    if (args == nullptr) {
        return std::make_shared<Boolean>(true);
    }

    auto cell = As<Cell>(args);
    std::shared_ptr<Object> last = nullptr;

    while (cell != nullptr) {
        auto expr = cell->GetFirst()->Eval();
        if (!Is<Number>(expr)) {
            throw RuntimeError("Comparison error");
        }

        if (last && predicate(As<Number>(last)->GetValue(), As<Number>(expr)->GetValue())) {
            return std::make_shared<Boolean>(false);
        }

        last = expr;
        cell = As<Cell>(cell->GetSecond());
    }

    return std::make_shared<Boolean>(true);
}

std::shared_ptr<Object> IsEqualFunction::Apply(std::shared_ptr<Object> args) {
    return CommonBooleanFunction(args, [](int a, int b) { return a != b; });
}

std::shared_ptr<Object> IsGreaterFunction::Apply(std::shared_ptr<Object> args) {
    return CommonBooleanFunction(args, [](int a, int b) { return a <= b; });
}

std::shared_ptr<Object> IsGreaterOrEqualFunction::Apply(std::shared_ptr<Object> args) {
    return CommonBooleanFunction(args, [](int a, int b) { return a < b; });
}

std::shared_ptr<Object> IsLessOrEqualFunction::Apply(std::shared_ptr<Object> args) {
    return CommonBooleanFunction(args, [](int a, int b) { return a > b; });
}

std::shared_ptr<Object> IsLessFunction::Apply(std::shared_ptr<Object> args) {
    return CommonBooleanFunction(args, [](int a, int b) { return a >= b; });
}
