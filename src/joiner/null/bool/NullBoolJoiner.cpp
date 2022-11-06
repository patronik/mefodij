
#include "../../../../include/joiner/null/bool/NullBoolJoiner.h"

namespace Mefodij {

    NullBoolJoiner::NullBoolJoiner() : Joiner({L"="})
    {}

    void NullBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVar()->setBool(right->getBool());
            left->setBool(right->getBool());
        }
    }

}
