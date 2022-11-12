
#include "../../../../include/joiner/string/null/StringNullJoiner.h"

namespace Mefodij {

    StringNullJoiner::StringNullJoiner() : Joiner({L"=", L"+", L"==", L"!="})
    {}

    void StringNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);
        if (op == L"+") {
            
        } else if (op == L"=") {
            if (left->getCharIndex() > -1) {
                throw new runtime_error("Cannot assign non string value to string character");
            }

            left->getVarRef()->setNull();
            left->setNull();
        } else if (op == L"==") {
            left->setBool(false);
        } else if (op == L"!=") {
            left->setBool(true);
        } 
    }

}
