
#include "../../../../include/joiner/array/null/ArrayNullJoiner.h"

namespace Mefodij {

    ArrayNullJoiner::ArrayNullJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void ArrayNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVarRef()->setNull();
            left->setNull();
        } else if (op == L"==") {
            left->setBool(false);
        } else if (op == L"!=") {
            left->setBool(true);
        } 
    }

}
