
#include "../../../../include/joiner/int/bool/IntBoolJoiner.h"

IntBoolJoiner::IntBoolJoiner() : Joiner({L"==", L"||", L"&&", L"="})
{}

void IntBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"==") {
        left->setBool(
            (bool) (left->getInt()) == right->getBool()
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
        left->getVar()->setInt((int)right->getBool());
    }
}
