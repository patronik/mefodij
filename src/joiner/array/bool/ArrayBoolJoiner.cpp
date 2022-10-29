
#include "../../../../include/joiner/array/bool/ArrayBoolJoiner.h"

ArrayBoolJoiner::ArrayBoolJoiner() : Joiner({L"="})
{}

void ArrayBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
    if (op == L"=") {
        left->getVar()->setBool(right->getBool());
    } 
}
