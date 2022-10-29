
#include "../../../../include/joiner/array/double/ArrayDoubleJoiner.h"

ArrayDoubleJoiner::ArrayDoubleJoiner() : Joiner({L"="})
{}

void ArrayDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
    if (op == L"=") {
        left->getVar()->setDouble(right->getDouble());
    } 
}
