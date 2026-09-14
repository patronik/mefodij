
#include "../../../../include/joiner/double/bool/DoubleBoolJoiner.h"
#include <cmath>

namespace Mefodij {

    DoubleBoolJoiner::DoubleBoolJoiner() : Joiner({L"==", L"!=", L"||", L"&&", L"=", L"+", L"-", L"*", L"/", L"%"})
    {
    }

    void DoubleBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        double rightDouble = right->getBool() ? 1.0 : 0.0;

        if (op == L"+") {
            left->setDouble(left->getDouble() + rightDouble);
        } else if (op == L"-") {
            left->setDouble(left->getDouble() - rightDouble);
        } else if (op == L"*") {
            left->setDouble(left->getDouble() * rightDouble);
        } else if (op == L"/") {
            if (rightDouble == 0.0) {
                throw runtime_error("Division by zero.");
            }
            left->setDouble(left->getDouble() / rightDouble);
        } else if (op == L"%") {
            if (rightDouble == 0.0) {
                throw runtime_error("Division by zero.");
            }
            left->setDouble(std::fmod(left->getDouble(), rightDouble));
        } else if (op == L"==") {
            left->setBool(
                (bool) (left->getDouble()) == right->getBool()
            );
        } else if (op == L"!=") {
            left->setBool(
                (bool) (left->getDouble()) != right->getBool()
            );
        } else if (op == L"||") {
            left->setBool(
                (bool) (left->getDouble()) || right->getBool()
            );
        } else if (op == L"&&") {
            left->setBool(
                (bool) (left->getDouble()) && right->getBool()
            );
        } else if (op == L"=") {
            left->getVarRef()->setDouble((int)right->getBool());
            left->setDouble((int)right->getBool());
        }
    }

}
