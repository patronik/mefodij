
#include "../../../../include/joiner/double/int/DoubleIntJoiner.h"

namespace Mefodij {

    DoubleIntJoiner::DoubleIntJoiner(): Joiner({L"+", L"-", L"*", L"/", L"%", L"==", L"!=", L">", L"<", L">=", L"<=", L"||", L"&&", L"="})
    {
    }

    void DoubleIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"+") {
            left->setDouble(left->getDouble() + (double) right->getInt());
        } else if (op == L"-") {
            left->setDouble(left->getDouble() - (double) right->getInt());
        } else if (op == L"*") {
            left->setDouble(left->getDouble() * (double) right->getInt());
        } else if (op == L"/") {
            if (right->getInt() == 0) {
                    throw runtime_error("Division by zero.");
                }
            left->setDouble(left->getDouble() / (double) right->getInt());
        }  else if (op == L"%") {
            left->setInt((int) left->getDouble() % right->getInt());
        } else if (op == L"==") {
            left->setBool(
                left->getDouble() == right->getInt()
            );
        } else if (op == L"!=") {
            left->setBool(
                left->getDouble() != right->getInt()
            );
        } else if (op == L">=") {
            left->setBool(
                left->getDouble() >= right->getInt()
            );
        } else if (op == L">") {
            left->setBool(
                left->getDouble() > right->getInt()
            );
        } else if (op == L"<") {
            left->setBool(
                left->getDouble() < right->getInt()
            );
        } else if (op == L"<=") {
            left->setBool(
                left->getDouble() <= right->getInt()
            );
        } else if (op == L"||") {
            left->setBool(
                left->getDouble() || right->getInt()
            );
        } else if (op == L"&&") {
            left->setBool(
                left->getDouble() && right->getInt()
            );
        } else if (op == L"=") { 
            left->getVarRef()->setDouble((double) right->getInt());
            left->setDouble((double) right->getInt());
        } 
    }

}