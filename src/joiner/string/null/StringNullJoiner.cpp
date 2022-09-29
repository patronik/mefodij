
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

        if (left->getCharIndex() > -1) {
            throw new runtime_error("Cannot assign non string value to string character");
        }

        left->getVar()->setNull();
        left->setNull(); 
    }
}
