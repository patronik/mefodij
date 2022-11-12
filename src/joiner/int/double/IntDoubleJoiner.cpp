
#include "../../../../include/joiner/int/double/IntDoubleJoiner.h"

namespace Mefodij {

    IntDoubleJoiner::IntDoubleJoiner(): Joiner({L"==", L"!=", L">=", L"<=", L"||", L"&&", L"=", L">", L"<", L"%", L"*", L"/", L"+", L"-"})
    {}

    void IntDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);
        if (op == L"+") {
            left->setInt(left->getInt() + right->getDouble());
        } else if (op == L"-") {
           left->setInt(left->getInt() - right->getDouble());
        } else if (op == L"/") {
            left->setInt(left->getInt() / right->getDouble());
        } else if (op == L"*") {
            left->setInt(left->getInt() * right->getDouble());
        } else if (op == L"%") {
            left->setInt(left->getInt() % (int) right->getDouble());
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
            left->getVarRef()->setInt((int)right->getDouble());
            left->setInt((int)right->getDouble());
        }
    }

}
