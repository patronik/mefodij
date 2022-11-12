
#include "../../../../include/joiner/string/int/StringIntJoiner.h"

namespace Mefodij {

    StringIntJoiner::StringIntJoiner() : Joiner({L"+", L"=", L"==", L"!="})
    {}

    void StringIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"+") {
            left->setString(
                left->getString() + Tools::to_wstring(right->getInt())
            );
        } else if (op == L"=") {
            if (left->getCharIndex() > -1) {
                throw new runtime_error("Cannot assign non string value to string character");
            }
            
            left->getVarRef()->setString(Tools::to_wstring(right->getInt()));
            left->setString(Tools::to_wstring(right->getInt()));
        } else if (op == L"==") {
            left->setBool(
                left->getString() == Tools::to_wstring(right->getInt())
            );
        } else if (op == L"!=") {
            left->setBool(
                left->getString() != Tools::to_wstring(right->getInt())
            );
        } 
    }

}
