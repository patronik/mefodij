
#include "../../../../include/joiner/int/double/IntDoubleJoiner.h"
#include <cmath>

namespace Mefodij {

    IntDoubleJoiner::IntDoubleJoiner(): Joiner({L"==", L"!=", L">=", L"<=", L"||", L"&&", L"=", L">", L"<", L"%", L"*", L"/", L"+", L"-"})
    {}

    void IntDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);
        if (op == L"+") {
            left->setDouble((double) left->getInt() + right->getDouble());
        } else if (op == L"-") {
           left->setDouble((double) left->getInt() - right->getDouble());
        } else if (op == L"/") {
            if (right->getDouble() == 0.0) {
                throw runtime_error("Division by zero.");
            }
            left->setDouble((double) left->getInt() / right->getDouble());
        } else if (op == L"*") {
            left->setDouble((double) left->getInt() * right->getDouble());
        } else if (op == L"%") {
            if (right->getDouble() == 0.0) {
                throw runtime_error("Division by zero.");
            }
            left->setDouble(std::fmod((double) left->getInt(), right->getDouble()));
        } else if (op == L"==") {
            left->setBool(
                left->getInt() == right->getDouble()
            );
        } else if (op == L"!=") {
            left->setBool(
                left->getInt() != right->getDouble()
            );
        } else if (op == L">=") {
            left->setBool(
                left->getInt() >= right->getDouble()
            );
        } else if (op == L"<=") {
            left->setBool(
                left->getInt() <= right->getDouble()
            );
        } else if (op == L"<") {
            left->setBool(
                left->getInt() < right->getDouble()
            );
        } else if (op == L">") {
            left->setBool(
                left->getInt() > right->getDouble()
            );
        } else if (op == L"||") {
            left->setBool(
                left->getInt() || right->getDouble()
            );
        } else if (op == L"&&") {
            left->setBool(
                left->getInt() && right->getDouble()
            );
        } else if (op == L"=") {
            left->getVarRef()->setDouble(right->getDouble());
            left->setDouble(right->getDouble());
        }
    }

}
