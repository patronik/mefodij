
#include "../../../../include/joiner/bool/int/BoolIntJoiner.h"

namespace Mefodij {

    BoolIntJoiner::BoolIntJoiner() : Joiner({L"==", L"!=", L"||", L"&&", L"=", L"+", L"-", L"*", L"/", L"%"})
    {}

    void BoolIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        long leftInt = left->getBool() ? 1 : 0;

        if (op == L"+") {
            left->setInt(leftInt + right->getInt());
        } else if (op == L"-") {
            left->setInt(leftInt - right->getInt());
        } else if (op == L"*") {
            left->setInt(leftInt * right->getInt());
        } else if (op == L"/") {
            if (right->getInt() == 0) {
                throw runtime_error("Division by zero.");
            }
            left->setInt(leftInt / right->getInt());
        } else if (op == L"%") {
            if (right->getInt() == 0) {
                throw runtime_error("Division by zero.");
            }
            left->setInt(leftInt % right->getInt());
        } else if (op == L"==") {
            left->setBool(
                left->getBool() == ((bool) right->getInt())
            );
        } else if (op == L"!=") {
            left->setBool(
                left->getBool() != ((bool) right->getInt())
            );
        } else if (op == L"||") {
            left->setBool(
                left->getBool() || ((bool) right->getInt())
            );
        } else if (op == L"&&") {
            left->setBool(
                left->getBool() && ((bool) right->getInt())
            );
        } else if (op == L"=") {
            left->getVarRef()->setBool((bool) right->getInt());
            left->setBool((bool) right->getInt());
        }
    }

}
