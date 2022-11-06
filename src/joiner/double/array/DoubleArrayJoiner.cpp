
#include "../../../../include/joiner/double/array/DoubleArrayJoiner.h"

namespace Mefodij {

    DoubleArrayJoiner::DoubleArrayJoiner() : Joiner({L"="})
    {
    }

    void DoubleArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") { 
            left->getVar()->setArray(right->getArray());
            left->setArray(right->getArray());
        }
    }

}
