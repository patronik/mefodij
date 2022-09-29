
#include "../../../../include/joiner/array/double/ArrayDoubleJoiner.h"

ArrayDoubleJoiner::ArrayDoubleJoiner() : Joiner({L"="})
{}

void ArrayDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
    if (op == L"=") {
        if (!left->getVar()) {
            throw runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setDouble(right->getDouble());
        left->setDouble(right->getDouble());
    } 
}
