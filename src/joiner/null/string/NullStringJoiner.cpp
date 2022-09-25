
#include "../../../../include/joiner/null/string/NullStringJoiner.h"

NullStringJoiner::NullStringJoiner() : Joiner({L"="})
{}

void NullStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"=") {
        if (!left->getVar()) {
            throw runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setString(right->getString());
        left->setString(right->getString());
    }
}
