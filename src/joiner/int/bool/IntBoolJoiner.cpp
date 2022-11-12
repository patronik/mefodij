
#include "../../../../include/joiner/int/bool/IntBoolJoiner.h"

namespace Mefodij {

    IntBoolJoiner::IntBoolJoiner() : Joiner({L"==", L"!=", L"||", L"&&", L"="})
    {}

    void IntBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"==") {
            left->setBool(
                (bool) (left->getInt()) == right->getBool()
            );
        } else if (op == L"!=") {
            left->setBool(
                (bool) (left->getInt()) != right->getBool()
            );
        } else if (op == L"||") {
            left->setBool(
                (bool) (left->getInt()) || right->getBool()
            );
        } else if (op == L"&&") {
            left->setBool(
                (bool) (left->getInt()) && right->getBool()
            );
        } else if (op == L"=") {
            left->getVarRef()->setInt((int)right->getBool());
            left->setInt((int)right->getBool());
        }
    }

}
