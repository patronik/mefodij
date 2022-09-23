
#include "../../../../include/joiner/double/int/DoubleIntJoiner.h"

DoubleIntJoiner::DoubleIntJoiner(): Joiner({L"+", L"-", L"*", L"/", L"%", L"==", L">", L"<", L">=", L"<=", L"||", L"&&", L"="})
{
}

void DoubleIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"+") {
        left->setDouble(left->getDouble() + right->getInt());
    } else if (op == L"-") {
        left->setDouble(left->getDouble() - right->getInt());
    } else if (op == L"*") {
        left->setDouble(left->getDouble() * right->getInt());
    } else if (op == L"/") {
        if (right->getInt() == 0) {
                throw new runtime_error("Division by zero");
            }
        left->setDouble(left->getDouble() / right->getInt());
    }  else if (op == L"%") {
        left->setDouble(
            (double) ((int)left->getDouble() % right->getInt())
        );
    } else if (op == L"==") {
        left->setBool(
            (bool) (left->getDouble() == right->getInt())
        );
    } else if (op == L">=") {
        left->setBool(
            (bool) (left->getDouble() >= right->getInt())
        );
    } else if (op == L">") {
        left->setBool(
            (bool) (left->getDouble() > right->getInt())
        );
    } else if (op == L"<") {
        left->setBool(
            (bool) (left->getDouble() < right->getInt())
        );
    } else if (op == L"<=") {
        left->setBool(
            (bool) (left->getDouble() <= right->getInt())
        );
    } else if (op == L"||") {
        left->setBool(
            (bool) (left->getDouble() || right->getInt())
        );
    } else if (op == L"&&") {
        left->setBool(
            (bool) (left->getDouble() && right->getInt())
        );
    } else if (op == L"=") {
        if (!left->getVar()) {
            throw new runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setDouble(right->getInt());
        left->setDouble(right->getInt());
    } 
}
