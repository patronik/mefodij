
#include "../../../../include/joiner/bool/int/BoolIntJoiner.h"

namespace Mefodij {

    BoolIntJoiner::BoolIntJoiner() : Joiner({L"==", L"!=", L"||", L"&&", L"="})
    {}

    void BoolIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"==") {
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
            left->getVar()->setBool((bool) right->getInt());
            left->setBool((bool) right->getInt());
        }
    }

}