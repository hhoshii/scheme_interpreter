#include "functions.h"
#include "boolean_functions.h"
#include "comparison_functions.h"
#include "integer_functions.h"
#include "pair_and_list_functions.h"
#include "error.h"

std::shared_ptr<Object> QuoteFunction::Apply(std::shared_ptr<Object> args) {
    auto cell = As<Cell>(args);
    if (!cell) {
        throw RuntimeError("wrong number of arguments for quote");
    }

    if (!cell->GetFirst()) {
        return nullptr;
    }

    return cell->GetFirst();
}

std::unordered_map<std::string, std::shared_ptr<Function>>& GetFunction() {
    static std::unordered_map<std::string, std::shared_ptr<Function>> functions = {
        {"boolean?", std::make_shared<IsBoolFunction>()},
        {"number?", std::make_shared<IsNumberFunction>()},
        {"symbol?", std::make_shared<IsSymbolFunction>()},
        {"pair?", std::make_shared<IsPairFunction>()},
        {"null?", std::make_shared<IsNullFunction>()},
        {"list?", std::make_shared<IsListFunction>()},
        {"list", std::make_shared<ListFunction>()},
        {"list-ref", std::make_shared<ListRefFunction>()},
        {"list-tail", std::make_shared<ListTailFunction>()},
        {"cons", std::make_shared<ConsFunction>()},
        {"car", std::make_shared<CarFunction>()},
        {"cdr", std::make_shared<CdrFunction>()},
        {"max", std::make_shared<MaxFunction>()},
        {"min", std::make_shared<MinFunction>()},
        {"abs", std::make_shared<AbsFunction>()},
        {"not", std::make_shared<NotFunction>()},
        {"quote", std::make_shared<QuoteFunction>()},
        {"and", std::make_shared<AndFunction>()},
        {"or", std::make_shared<OrFunction>()},
        {"=", std::make_shared<IsEqualFunction>()},
        {">", std::make_shared<IsGreaterFunction>()},
        {"<", std::make_shared<IsLessFunction>()},
        {"<=", std::make_shared<IsLessOrEqualFunction>()},
        {">=", std::make_shared<IsGreaterOrEqualFunction>()},
        {"+", std::make_shared<AddFunction>()},
        {"-", std::make_shared<MinusFunction>()},
        {"*", std::make_shared<MulFunction>()},
        {"/", std::make_shared<DivFunction>()},
    };
    return functions;
}
