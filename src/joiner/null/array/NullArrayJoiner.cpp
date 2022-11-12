
#include "../../../../include/joiner/null/array/NullArrayJoiner.h"

namespace Mefodij {

    NullArrayJoiner::NullArrayJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void NullArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVarRef()->setArray(right->getArray());
            left->setArray(right->getArray());
        } else if (op == L"==") {
            left->setBool(false);
        } else if (op == L"!=") {
            left->setBool(true);
        } 
    }

}
