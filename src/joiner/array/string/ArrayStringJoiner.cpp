
#include "../../../../include/joiner/array/string/ArrayStringJoiner.h"

namespace Mefody {

    ArrayStringJoiner::ArrayStringJoiner() : Joiner({L"="})
    {}

    void ArrayStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);
        if (op == L"=") {
            left->getVar()->setString(right->getString());
            left->setString(right->getString());
        } 
    }

}
