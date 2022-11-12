
#include "../../../../include/joiner/array/int/ArrayIntJoiner.h"

namespace Mefodij {

    ArrayIntJoiner::ArrayIntJoiner() : Joiner({L"=", L"=="})
    {}

    void ArrayIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);
        if (op == L"=") {
            left->getVarRef()->setInt(right->getInt());
            left->setInt(right->getInt());
        } else if (op == L"==") {
            left->setBool(false);
        }
    }

}
