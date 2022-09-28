
#include "../../../../include/joiner/string/bool/StringBoolJoiner.h"

StringBoolJoiner::StringBoolJoiner() : Joiner({L"==", L"||", L"&&", L"="})
{}

void StringBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"==") {
        left->setBool(
            (bool) (left->getString().size() > 0) == right->getBool()
        );
    } else if (op == L"||") {
         left->setBool(
            (bool) (left->getString().size() > 0) || right->getBool()
         );
    } else if (op == L"&&") {
        left->setBool(
            (bool) (left->getString().size() > 0) && right->getBool()
        );
    } else if (op == L"=") {
        if (!left->getVar()) {
            throw runtime_error("Assignment can only be done to variable");                    
        } 

        if (left->getCharIndex() > 0) {
            throw new runtime_error("Cannot assign non string value to string character");
        }
        
        left->getVar()->setBool(right->getBool());
        left->setBool(right->getBool()); 
    }
}
