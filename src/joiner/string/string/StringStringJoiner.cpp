
#include "../../../../include/joiner/string/string/StringStringJoiner.h"

#include <regex>
namespace Mefody {

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
            if (left->getString() == right->getString()) {
                left->setBool(true);
            } else {
                left->setBool(false);
            }
        } else if (op == L"!=") {
            if (left->getString() != right->getString()) {
                left->setBool(true);
            } else {
                left->setBool(false);
            }
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
                left->getVar()->setStringChar(right->getString().at(0), left->getCharIndex());        
            } else {
                left->getVar()->setString(right->getString());
            } 
        }
    }

}
