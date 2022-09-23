
#include "../../../../include/joiner/null/int/NullIntJoiner.h"

NullIntJoiner::NullIntJoiner() : Joiner({L"="})
{}

void NullIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"=") {
        if (!left->getVar()) {
            throw new runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setInt(right->getInt());
        left->setInt(right->getInt());
    }
}
