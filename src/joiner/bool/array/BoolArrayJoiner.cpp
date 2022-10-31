
#include "../../../../include/joiner/bool/array/BoolArrayJoiner.h"

namespace Mefody {

    BoolArrayJoiner::BoolArrayJoiner() : Joiner({L"="})
    {}

    void BoolArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVar()->setArray(right->getArray());
            left->setArray(right->getArray());
        }
    }

}