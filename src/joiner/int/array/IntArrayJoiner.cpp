
#include "../../../../include/joiner/int/array/IntArrayJoiner.h"

namespace Mefodij {

    IntArrayJoiner::IntArrayJoiner() : Joiner({L"="})
    {}

    void IntArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") { 
            left->getVar()->setArray(right->getArray());
            left->setArray(right->getArray());
        }
    }

}
