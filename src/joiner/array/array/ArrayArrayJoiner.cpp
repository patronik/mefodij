
#include "../../../../include/joiner/array/array/ArrayArrayJoiner.h"

ArrayArrayJoiner::ArrayArrayJoiner() : Joiner({L"="})
{}

void ArrayArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
    if (op == L"=") {
        left->getVar()->setArray(right->getArray());
        left->setArray(right->getArray());
    } 
}
