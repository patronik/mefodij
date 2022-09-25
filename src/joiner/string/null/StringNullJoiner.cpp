
#include "../../../../include/joiner/string/null/StringNullJoiner.h"

StringNullJoiner::StringNullJoiner() : Joiner({L"="})
{}

void StringNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"=") {
        if (!left->getVar()) {
            throw runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setNull();
        left->setNull(); 
    }
}
