
#include "../../../../include/joiner/bool/null/BoolNullJoiner.h"

BoolNullJoiner::BoolNullJoiner() : Joiner({L"="})
{}

void BoolNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
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
