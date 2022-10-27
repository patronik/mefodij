
#include "../../../../include/joiner/null/array/NullArrayJoiner.h"

NullArrayJoiner::NullArrayJoiner() : Joiner({L"="})
{}

void NullArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"=") {
        left->getVar()->setArray(right->getArray());
        left->setArray(right->getArray());
    }  
}
