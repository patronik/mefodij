
#include "../../../../include/joiner/string/string/StringStringJoiner.h"

#include <regex>

StringStringJoiner::StringStringJoiner() : Joiner({L".", L"=", L"матч"})
{}

void StringStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L".") {
        left->setString(
            left->getString() + right->getString()
        );
    } else if (op == L"матч") {
        if (regex_match(left->getString(), wregex(right->getString()))) {
            left->setBool(true);
        } else {
            left->setBool(false);
        }
    } else if (op == L"=") {
        if (!left->getVar()) {
            throw new runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setString(right->getString());
        left->setString(right->getString()); 
    }
}
