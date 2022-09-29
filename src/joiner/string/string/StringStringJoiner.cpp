
#include "../../../../include/joiner/string/string/StringStringJoiner.h"

#include <regex>

StringStringJoiner::StringStringJoiner() : Joiner({L".", L"=", L"~"})
{}

void StringStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L".") {
        left->setString(
            left->getString() + right->getString()
        );
    } else if (op == L"~") {
        if (regex_match(left->getString(), wregex(right->getString()))) {
            left->setBool(true);
        } else {
            left->setBool(false);
        }
    } else if (op == L"=") {
        if (!left->getVar()) {
            throw runtime_error("Assignment can only be done to variable");                    
        } 

        if (left->getCharIndex() > -1) {
            // single character string
            if (right->getString().size() > 1) {
                throw runtime_error("Cannot assign multiple characters to one");
            }
            left->getVar()->setStringChar(right->getString().at(0), left->getCharIndex());  
            left->setStringChar(right->getString().at(0), 0);         
        } else {
            left->getVar()->setString(right->getString());
            left->setString(right->getString()); 
        } 
    }
}
