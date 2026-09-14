
#include "../../../../include/joiner/bool/double/BoolDoubleJoiner.h"
#include <cmath>

namespace Mefodij {

    BoolDoubleJoiner::BoolDoubleJoiner() : Joiner({L"==", L"!=", L"||", L"&&", L"=", L"+", L"-", L"*", L"/", L"%"})
    {}

    void BoolDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        double leftDouble = left->getBool() ? 1.0 : 0.0;

        if (op == L"+") {
            left->setDouble(leftDouble + right->getDouble());
        } else if (op == L"-") {
            left->setDouble(leftDouble - right->getDouble());
        } else if (op == L"*") {
            left->setDouble(leftDouble * right->getDouble());
        } else if (op == L"/") {
            if (right->getDouble() == 0.0) {
                throw runtime_error("Division by zero.");
            }
            left->setDouble(leftDouble / right->getDouble());
        } else if (op == L"%") {
            if (right->getDouble() == 0.0) {
                throw runtime_error("Division by zero.");
            }
            left->setDouble(std::fmod(leftDouble, right->getDouble()));
        } else if (op == L"==") {
            left->setBool(
                left->getBool() == ((bool) right->getDouble())
            );
        } else if (op == L"!=") {
            left->setBool(
                left->getBool() != ((bool) right->getDouble())
            );
        } else if (op == L"||") {
            left->setBool(
                left->getBool() || ((bool) right->getDouble())
            );
        } else if (op == L"&&") {
            left->setBool(
                left->getBool() && ((bool) right->getDouble())
            );
        } else if (op == L"=") {
            left->getVarRef()->setBool((bool) right->getDouble());
            left->setBool((bool) right->getDouble());
        } 
    }

}
