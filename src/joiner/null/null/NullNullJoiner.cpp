
#include "../../../../include/joiner/null/null/NullNullJoiner.h"

namespace Mefodij {

    NullNullJoiner::NullNullJoiner() : Joiner({L"=", L"==", L"!=", L"+", L"-"})
    {}

    void NullNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"+") {
            left->setNull();
        } if (op == L"-") {
            left->setNull();
        } else if (op == L"==") {
            left->setBool(true);
        } else if (op == L"!=") {
            left->setBool(false);
        } else if (op == L"=") {
            left->getVarRef()->setNull();
            left->setNull();
        } 
    }

}
