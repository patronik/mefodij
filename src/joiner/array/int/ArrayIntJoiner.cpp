
#include "../../../../include/joiner/array/int/ArrayIntJoiner.h"

namespace Mefody {

    ArrayIntJoiner::ArrayIntJoiner() : Joiner({L"="})
    {}

    void ArrayIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);
        if (op == L"=") {
            left->getVar()->setInt(right->getInt());
        } 
    }

}
