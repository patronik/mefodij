
#include "../../../../include/joiner/bool/double/BoolDoubleJoiner.h"

namespace Mefody {

    BoolDoubleJoiner::BoolDoubleJoiner() : Joiner({L"==", L"||", L"&&", L"="})
    {}

    void BoolDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"==") {
            left->setBool(
                left->getBool() == ((bool) right->getDouble())
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
        }
    }

}
