
#include "../../../../include/joiner/string/string/StringStringJoiner.h"

#include <regex>
namespace Mefodij {

    StringStringJoiner::StringStringJoiner() : Joiner({L"+", L"=", L"~", L"==", L"!="})
    {}

    void StringStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"+") {
            left->setString(
                left->getString() + right->getString()
            );
        } else if (op == L"==") {
            left->setBool(left->getString() == right->getString());
        } else if (op == L"!=") {
            left->setBool(left->getString() != right->getString());
        } else if (op == L"~") {
            if (regex_match(left->getString(), wregex(right->getString()))) {
                left->setBool(true);
            } else {
                left->setBool(false);
            }
        } else if (op == L"=") {
            if (left->getCharIndex() > -1) {
                // single character string
                if (right->getString().size() > 1) {
                    throw runtime_error("Cannot assign multiple characters to one");
                }
                left->getVarRef()->setStringChar(right->getString().at(0), left->getCharIndex());
                left->setStringChar(right->getString().at(0), 0);
            } else {
                left->getVarRef()->setString(right->getString());
                left->setString(right->getString());
            } 
        }
    }

}
