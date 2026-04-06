#include "object.h"

#include "boolean_functions.h"
#include "functions.h"
#include "environment.h"
#include "mylambda.h"

Object::Object() = default;

std::shared_ptr<Object> Object::Eval() {
    return shared_from_this();
}

std::string Object::Serialize() {
    throw RuntimeError("Serialize wrong object");
}

Object::~Object() = default;

Number::Number(int value) : value_(value) {
}

Boolean::Boolean(bool value) : value_(value) {
}

Symbol::Symbol(std::string value) : value_(value) {
}

Cell::Cell(std::shared_ptr<Object> first, std::shared_ptr<Object> second)
    : first_(first), second_(second) {
}

int Number::GetValue() const {
    return value_;
}

bool Boolean::GetValue() const {
    return value_;
}

const std::string& Symbol::GetName() const {
    return value_;
}

std::shared_ptr<Object> Cell::GetFirst() const {
    return first_;
}

std::shared_ptr<Object> Cell::GetSecond() const {
    return second_;
}

void Cell::SetFirst(std::shared_ptr<Object> val) {
    first_ = val;
}

void Cell::SetSecond(std::shared_ptr<Object> val) {
    second_ = val;
}

std::shared_ptr<Object> CloseBracket::Eval() {
    throw SyntaxError("invalid syntax for list");
}

std::string CloseBracket::Serialize() {
    throw SyntaxError("invalid syntax for list");
}

std::shared_ptr<Object> Number::Eval() {
    return shared_from_this();
}

std::shared_ptr<Object> Boolean::Eval() {
    return shared_from_this();
}

std::shared_ptr<Object> Symbol::Eval() {
    return current_env->Get(value_);
}

std::shared_ptr<Object> IfEval(std::shared_ptr<Cell> args) {
    if (!args) {
        throw SyntaxError("invalid syntax for if");
    }

    auto expr = args->GetFirst();
    auto branches = args->GetSecond();
    if (!branches) {
        throw SyntaxError("no branches in if");
    }

    auto true_expr = As<Cell>(branches)->GetFirst();
    auto false_expr = As<Cell>(branches)->GetSecond();
    if (Is<Cell>(false_expr) && As<Cell>(false_expr)->GetSecond()) {
        throw SyntaxError("too many arguments in if");
    }

    auto evaluated_expr = expr->Eval();

    if (As<Boolean>(evaluated_expr)->GetValue()) {
        return true_expr->Eval();
    } else {
        if (!false_expr) {
            return nullptr;
        }
        return As<Cell>(false_expr)->GetFirst()->Eval();
    }
}

std::shared_ptr<Object> DefineEval(std::shared_ptr<Cell> args) {
    if (!args) {
        throw SyntaxError("invalid syntax for define");
    }

    auto check_cell = args->GetFirst();

    if (Is<Cell>(check_cell)) {
        std::string fn_name = As<Cell>(check_cell)->GetFirst()->Serialize();
        auto params = As<Cell>(check_cell)->GetSecond();
        auto body = args->GetSecond();
        auto proc = std::make_shared<MyLambda>(As<Cell>(params), As<Cell>(body), current_env);
        current_env->Define(fn_name, proc);
        return nullptr;
    }

    if (!Is<Symbol>(check_cell)) {
        throw SyntaxError("invalid name of variable in define");
    }

    auto second = args->GetSecond();
    if (!second || !Is<Cell>(second) || As<Cell>(second)->GetSecond()) {
        throw SyntaxError("wrong num of objects in define");
    }

    auto val = As<Cell>(second)->GetFirst()->Eval();

    current_env->Define(As<Symbol>(check_cell)->Serialize(), val);
    return nullptr;
}

std::shared_ptr<Object> SetEval(std::shared_ptr<Cell> args) {
    if (!args) {
        throw SyntaxError("invalid syntax for set");
    }

    auto check_cell = args->GetFirst();

    if (Is<Cell>(check_cell)) {
        std::string fn_name = As<Cell>(check_cell)->GetFirst()->Serialize();
        auto params = As<Cell>(check_cell)->GetSecond();
        auto body = args->GetSecond();
        auto proc = std::make_shared<MyLambda>(As<Cell>(params), As<Cell>(body), current_env);
        current_env->Set(fn_name, proc);
        return nullptr;
    }

    if (!Is<Symbol>(check_cell)) {
        throw SyntaxError("invalid name of variable in set");
    }
    auto second = args->GetSecond();
    if (!second || !Is<Cell>(second) || As<Cell>(second)->GetSecond()) {
        throw SyntaxError("wrong num of objects in set");
    }

    auto val = As<Cell>(second)->GetFirst()->Eval();
    current_env->Set(As<Symbol>(check_cell)->Serialize(), val);
    return nullptr;
}

std::shared_ptr<Object> SetCarEval(std::shared_ptr<Cell> args) {
    if (!args) {
        throw SyntaxError("invalid syntax for setcar");
    }

    auto cell_check = args->GetFirst();
    if (Is<Symbol>(cell_check)) {
        cell_check = current_env->Get(As<Symbol>(cell_check)->GetName());
    } else {
        cell_check = cell_check->Eval();
    }

    if (!Is<Cell>(cell_check)) {
        throw SyntaxError("invalid name of variable in setcar");
    }

    auto second = args->GetSecond();
    if (!second || !Is<Cell>(second) || As<Cell>(second)->GetSecond()) {
        throw SyntaxError("wrong num of objects in setcar");
    }

    auto val = As<Cell>(second)->GetFirst()->Eval();
    As<Cell>(cell_check)->SetFirst(val);

    return nullptr;
}

std::shared_ptr<Object> SetCdrEval(std::shared_ptr<Cell> args) {
    if (!args) {
        throw SyntaxError("invalid syntax for setcar");
    }

    auto cell_check = args->GetFirst();
    if (Is<Symbol>(cell_check)) {
        cell_check = current_env->Get(As<Symbol>(cell_check)->GetName());
    } else {
        cell_check = cell_check->Eval();
    }

    if (!Is<Cell>(cell_check)) {
        throw SyntaxError("invalid name of variable in setcar");
    }

    auto second = args->GetSecond();
    if (!second || !Is<Cell>(second) || As<Cell>(second)->GetSecond()) {
        throw SyntaxError("wrong num of objects in setcar");
    }

    auto val = As<Cell>(second)->GetFirst()->Eval();
    As<Cell>(cell_check)->SetSecond(val);

    return nullptr;
}

std::shared_ptr<Object> LambdaEval(std::shared_ptr<Cell> args) {
    if (!args) {
        throw SyntaxError("invalid syntax for lambda");
    }
    auto params = As<Cell>(args->GetFirst());
    auto body = As<Cell>(args->GetSecond());
    if (!body) {
        throw SyntaxError("no expressions");
    }

    return std::make_shared<MyLambda>(params, body, current_env);
}

std::shared_ptr<Object> Cell::Eval() {
    if (GetFirst() == nullptr) {
        throw RuntimeError("something bad");
    }

    // сори за эту часть, надеюсь я позже приведу ее в нормальный вид
    // если вы это читаете, то я этого не сделал ¯\_(ツ)_/¯

    if (Is<Symbol>(GetFirst())) {
        auto op = GetFirst()->Serialize();

        if (op == "quote") {
            auto args = As<Cell>(GetSecond());
            if (!args) {
                return nullptr;
            }

            auto quoted = args->GetFirst();
            if (!quoted) {
                return nullptr;
            }
            return quoted;
        }

        if (op == "if") {
            return IfEval(As<Cell>(GetSecond()));
        }

        if (op == "define") {
            return DefineEval(As<Cell>(GetSecond()));
        }

        if (op == "set!") {
            return SetEval(As<Cell>(GetSecond()));
        }

        if (op == "set-car!") {
            return SetCarEval(As<Cell>(GetSecond()));
        }

        if (op == "set-cdr!") {
            return SetCdrEval(As<Cell>(GetSecond()));
        }

        if (op == "lambda") {
            return LambdaEval(As<Cell>(GetSecond()));
        }

        if (GetFunction().find(op) != GetFunction().end() && !current_env->Check(op)) {
            return GetFunction()[op]->Apply(GetSecond());
        }
    }
    auto op = GetFirst()->Eval();

    std::shared_ptr<Cell> evaluated_args_begin = nullptr;
    std::shared_ptr<Cell> evaluated_args_end = nullptr;
    auto args_iter = GetSecond();
    if (args_iter && Is<Cell>(args_iter)) {
        auto arg_expr = As<Cell>(args_iter)->GetFirst();
        if (arg_expr) {
            arg_expr = arg_expr->Eval();
        }

        auto node = std::make_shared<Cell>(arg_expr, nullptr);

        evaluated_args_begin = node;
        evaluated_args_end = node;
        args_iter = As<Cell>(args_iter)->GetSecond();
    }

    while (args_iter && Is<Cell>(args_iter)) {
        auto arg_expr = As<Cell>(args_iter)->GetFirst();
        if (arg_expr) {
            arg_expr = arg_expr->Eval();
        }

        auto node = std::make_shared<Cell>(arg_expr, nullptr);

        evaluated_args_end->SetSecond(node);
        evaluated_args_end = node;
        args_iter = As<Cell>(args_iter)->GetSecond();
    }

    if (Is<MyLambda>(op)) {
        return As<MyLambda>(op)->Apply(evaluated_args_begin);
    }

    if (Is<Function>(op)) {
        return As<Function>(op)->Apply(evaluated_args_begin);
    }

    throw RuntimeError("invalid function");
}

std::string Number::Serialize() {
    return std::to_string(value_);
}

std::string Boolean::Serialize() {
    if (value_) {
        return "#t";
    }
    return "#f";
}

std::string Symbol::Serialize() {
    return value_;
}

std::string Cell::Serialize() {
    std::string res = "(";

    if (GetFirst()) {
        res += GetFirst()->Serialize();
    } else {
        res += "()";
    }

    auto cur = GetSecond();
    while (cur && Is<Cell>(cur)) {
        auto c = As<Cell>(cur);
        res += " ";
        if (c->GetFirst()) {
            res += c->GetFirst()->Serialize();
        } else {
            res += "()";
        }
        cur = c->GetSecond();
    }

    if (cur && !Is<CloseBracket>(cur)) {
        res += " . " + cur->Serialize();
    }

    res += ")";
    return res;
}

void Cell::SetQuote() {
    is_quote_ = true;
}

bool Cell::IsQuote() {
    return is_quote_;
}

std::shared_ptr<Object> EmptyObject::Eval() {
    return shared_from_this();
}

std::string EmptyObject::Serialize() {
    return "()";
}
