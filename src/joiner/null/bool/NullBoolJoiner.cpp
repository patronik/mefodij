
#include "../../../../include/joiner/null/bool/NullBoolJoiner.h"

NullBoolJoiner::NullBoolJoiner() : Joiner({L"="})
{}

void NullBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
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
