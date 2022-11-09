
#include "../../../../include/joiner/bool/double/BoolDoubleJoiner.h"

namespace Mefodij {

    BoolDoubleJoiner::BoolDoubleJoiner() : Joiner({L"==", L"!=", L"||", L"&&", L"="})
    {}

    void BoolDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"==") {
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
            left->getVar()->setBool((bool) right->getDouble());
            left->setBool((bool) right->getDouble());
        } 
    }

}
