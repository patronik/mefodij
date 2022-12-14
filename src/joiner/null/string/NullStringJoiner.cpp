
#include "../../../../include/joiner/null/string/NullStringJoiner.h"

namespace Mefodij {

    NullStringJoiner::NullStringJoiner() : Joiner({L"=", L"+", L"==", L"!="})
    {}

    void NullStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);
        if (op == L"+") {
            left->setString(right->getString());
        } else if (op == L"=") { 
            left->getVarRef()->setString(right->getString());
            left->setString(right->getString());
        } else if (op == L"==") {
            left->setBool(false);
        }  else if (op == L"!=") {
            left->setBool(true);
        } 
    }

}
