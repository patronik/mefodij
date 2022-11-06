
#include "../../../../include/joiner/int/null/IntNullJoiner.h"

namespace Mefodij {

    IntNullJoiner::IntNullJoiner() : Joiner({L"="})
    {}

    void IntNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVar()->setNull();
            left->setNull();
        }
    }

}
