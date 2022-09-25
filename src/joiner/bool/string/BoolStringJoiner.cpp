
#include "../../../../include/joiner/bool/string/BoolStringJoiner.h"

BoolStringJoiner::BoolStringJoiner() : Joiner({L"="})
{}

void BoolStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"=") {
        if (!left->getVar()) {
            throw runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setBool(right->getString().size() > 0);
        left->setBool(right->getString().size() > 0); 
    }
}
