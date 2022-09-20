
#include "../../../../include/joiner/int/null/IntNullJoiner.h"

IntNullJoiner::IntNullJoiner() : Joiner({L"="})
{}

void IntNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
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
