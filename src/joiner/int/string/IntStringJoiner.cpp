
#include "../../../../include/joiner/int/string/IntStringJoiner.h"

namespace Mefodij {

    IntStringJoiner::IntStringJoiner(): Joiner({L"+", L"=", L"==", L"!="})
    {}

    void IntStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);
        
        if (op == L"+") {
            left->setString(
                to_wstring(left->getInt()) + right->getString()
            );
        } else if (op == L"=") {
           left->getVar()->setString(right->getString());
           left->setString(right->getString());
        } else if (op == L"==") {
            left->setBool(
                to_wstring(left->getInt()) == right->getString()
            );
        } else if (op == L"!=") {
            left->setBool(
                to_wstring(left->getInt()) != right->getString()
            );
        } 
    }

}
