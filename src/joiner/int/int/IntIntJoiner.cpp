
#include "../../../../include/joiner/int/int/IntIntJoiner.h"

IntIntJoiner::IntIntJoiner(): Joiner({L"+", L"-", L"*", L"/", L"%", L"==", L">", L"<", L">=", L"<=", L"||", L"&&", L"="})
{
}

void IntIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"+") {
        left->setInt(left->getInt() + right->getInt());
    } else if (op == L"-") {
        left->setInt(left->getInt() - right->getInt());
    } else if (op == L"*") {
        left->setInt(left->getInt() * right->getInt());
    } else if (op == L"/") {
        if (right->getInt() == 0) {
                throw runtime_error("Division by zero");
            }
        left->setInt(left->getInt() / right->getInt());
    }  else if (op == L"%") {
        left->setDouble(
            (double) (left->getInt() % right->getInt())
        );
    } else if (op == L"==") {
        left->setBool(
            (bool) (left->getInt() == right->getInt())
        );
    } else if (op == L">=") {
        left->setBool(
            (bool) (left->getInt() >= right->getInt())
        );
    } else if (op == L">") {
        left->setBool(
            (bool) (left->getInt() > right->getInt())
        );
    } else if (op == L"<") {
        left->setBool(
            (bool) (left->getInt() < right->getInt())
        );
    } else if (op == L"<=") {
        left->setBool(
            (bool) (left->getInt() <= right->getInt())
        );
    } else if (op == L"||") {
        left->setBool(
            (bool) (left->getInt() || right->getInt())
        );
    } else if (op == L"&&") {
        left->setBool(
            (bool) (left->getInt() && right->getInt())
        );
    } else if (op == L"=") {
        if (!left->getVar()) {
            throw runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setInt(right->getInt());
        left->setInt(right->getInt());
    } 
}
