
#include "../../../../include/joiner/null/double/NullDoubleJoiner.h"

NullDoubleJoiner::NullDoubleJoiner() : Joiner({L"="})
{}

void NullDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"=") {
        if (!left->getVar()) {
            throw new runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setDouble(right->getDouble());
        left->setDouble(right->getDouble());
    }
}
