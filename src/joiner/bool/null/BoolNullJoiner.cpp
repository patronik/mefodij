
#include "../../../../include/joiner/bool/null/BoolNullJoiner.h"

namespace Mefodij {

    BoolNullJoiner::BoolNullJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void BoolNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
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
