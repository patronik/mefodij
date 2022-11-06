
#include "../../../../include/joiner/bool/null/BoolNullJoiner.h"

namespace Mefodij {

    BoolNullJoiner::BoolNullJoiner() : Joiner({L"="})
    {}

    void BoolNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVar()->setNull();
            left->setNull();
        }
    }

}
