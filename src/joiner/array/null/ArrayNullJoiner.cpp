
#include "../../../../include/joiner/array/null/ArrayNullJoiner.h"

ArrayNullJoiner::ArrayNullJoiner() : Joiner({L"="})
{}

void ArrayNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"=") {
        if (!left->getVar()) {
            throw new runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setNull();
        left->setNull(); 
    }
}
