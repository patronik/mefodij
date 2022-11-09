
#include "../../../../include/joiner/double/null/DoubleNullJoiner.h"

namespace Mefodij {

    DoubleNullJoiner::DoubleNullJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void DoubleNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") { 
            left->getVar()->setNull();
            left->setNull();
        } else if (op == L"==") {
            left->setBool(false);
        } else if (op == L"!=") {
            left->setBool(true);
        } 
    }

}