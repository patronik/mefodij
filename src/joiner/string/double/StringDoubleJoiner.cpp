
#include "../../../../include/joiner/string/double/StringDoubleJoiner.h"

namespace Mefodij {

    StringDoubleJoiner::StringDoubleJoiner() : Joiner({L"+", L"=", L"==", L"!="})
    {}

    void StringDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"+") {
            left->setString(
                left->getString() + Tools::to_wstring(right->getDouble())
            );
        } else if (op == L"=") {
            if (left->getCharIndex() > -1) {
                throw new runtime_error("Cannot assign non string value to string character");
            }
            
            left->getVar()->setString(Tools::to_wstring(right->getDouble()));
            left->setString(Tools::to_wstring(right->getDouble()));
        } else if (op == L"==") {
            left->setBool(
                left->getString() == Tools::to_wstring(right->getDouble())
            );
        } else if (op == L"!=") {
            left->setBool(
                left->getString() != Tools::to_wstring(right->getDouble())
            );
        } 
    }

}
