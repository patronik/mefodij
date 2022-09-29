
#include "../../../../include/joiner/array/int/ArrayIntJoiner.h"

ArrayIntJoiner::ArrayIntJoiner() : Joiner({L"="})
{}

void ArrayIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
    if (op == L"=") {
        if (!left->getVar()) {
            throw runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setInt(right->getInt());
        left->setInt(right->getInt());
    } 
}
