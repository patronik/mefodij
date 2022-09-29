
#include "../../../../include/joiner/array/bool/ArrayBoolJoiner.h"

ArrayBoolJoiner::ArrayBoolJoiner() : Joiner({L"="})
{}

void ArrayBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
    if (op == L"=") {
        if (!left->getVar()) {
            throw runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setBool(right->getBool());
        left->setBool(right->getBool());
    } 
}
