
#include "../../../../include/joiner/bool/bool/BoolBoolJoiner.h"

BoolBoolJoiner::BoolBoolJoiner() : Joiner({L"==", L"||", L"&&", L"="})
{}

void BoolBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"==") {
        left->setBool(
            (bool) (left->getBool()) == right->getBool()
        );
    } else if (op == L"||") {
         left->setBool(
            (bool) (left->getBool()) || right->getBool()
         );
    } else if (op == L"&&") {
        left->setBool(
            (bool) (left->getBool()) && right->getBool()
        );
    } else if (op == L"=") {
        left->getVar()->setBool(right->getBool());
        left->setBool(right->getBool()); 
    }
}
