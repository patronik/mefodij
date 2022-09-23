
#include "../../../../include/joiner/string/double/StringDoubleJoiner.h"

StringDoubleJoiner::StringDoubleJoiner() : Joiner({L".", L"="})
{}

void StringDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L".") {
        left->setString(
            left->getString() + to_wstring(right->getDouble())
        );
    } else if (op == L"=") {
        if (!left->getVar()) {
            throw new runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setString(to_wstring(right->getDouble()));
        left->setString(to_wstring(right->getDouble())); 
    }
}
