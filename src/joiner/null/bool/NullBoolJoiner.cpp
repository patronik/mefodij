
#include "../../../../include/joiner/null/bool/NullBoolJoiner.h"

namespace Mefodij {

    NullBoolJoiner::NullBoolJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void NullBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVarRef()->setBool(right->getBool());
            left->setBool(right->getBool());
        } else if (op == L"==") {
            left->setBool(false);
        } else if (op == L"!=") {
            left->setBool(true);
        } 
    }

}
