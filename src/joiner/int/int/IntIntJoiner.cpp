
#include "../../../../include/joiner/int/int/IntIntJoiner.h"

namespace Mefodij {

    IntIntJoiner::IntIntJoiner(): Joiner({L"+", L"-", L"*", L"/", L"%", L"==", L">", L"<", L">=", L"<=", L"||", L"&&", L"=", L"!="})
    {}

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
                    throw runtime_error("Division by zero.");
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
        } else if (op == L"!=") {
            left->setBool(
                (bool) (left->getInt() != right->getInt())
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
            left->getVarRef()->setInt(right->getInt());
            left->setInt(right->getInt());
        } 
    }

}