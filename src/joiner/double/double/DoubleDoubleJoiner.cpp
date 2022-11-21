
#include "../../../../include/joiner/double/double/DoubleDoubleJoiner.h"

namespace Mefodij {

    DoubleDoubleJoiner::DoubleDoubleJoiner(): Joiner({L"+", L"-", L"*", L"/", L"%", L"==", L">", L"<", L">=", L"<=", L"||", L"&&", L"=", L"!="})
    {
    }

    void DoubleDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"+") {
            left->setDouble(left->getDouble() + right->getDouble());
        } else if (op == L"-") {
            left->setDouble(left->getDouble() - right->getDouble());
        } else if (op == L"*") {
            left->setDouble(left->getDouble() * right->getDouble());
        } else if (op == L"/") {
            if (right->getDouble() == 0.0) {
                    throw runtime_error("Division by zero.");
                }
            left->setDouble(left->getDouble() / right->getDouble());
        }  else if (op == L"%") {
            left->setInt((int) left->getDouble() % (int) right->getDouble());
        } else if (op == L"==") {
            left->setBool(
                (bool) (left->getDouble() == right->getDouble())
            );
        } else if (op == L"!=") {
            left->setBool(
                (bool) (left->getDouble() != right->getDouble())
            );
        } else if (op == L">=") {
            left->setBool(
                (bool) (left->getDouble() >= right->getDouble())
            );
        } else if (op == L">") {
            left->setBool(
                (bool) (left->getDouble() > right->getDouble())
            );
        } else if (op == L"<") {
            left->setBool(
                (bool) (left->getDouble() < right->getDouble())
            );
        } else if (op == L"<=") {
            left->setBool(
                (bool) (left->getDouble() <= right->getDouble())
            );
        } else if (op == L"||") {
            left->setBool(
                (bool) (left->getDouble() || right->getDouble())
            );
        } else if (op == L"&&") {
            left->setBool(
                (bool) (left->getDouble() && right->getDouble())
            );
        } else if (op == L"=") { 
            left->getVarRef()->setDouble(right->getDouble());
            left->setDouble(right->getDouble());
        } 
    }

}
