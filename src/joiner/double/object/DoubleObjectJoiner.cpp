#include "../../../../include/joiner/double/object/DoubleObjectJoiner.h"

namespace Mefodij {

    DoubleObjectJoiner::DoubleObjectJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void DoubleObjectJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVarRef()->setObject(right->getObject());
            left->setObject(right->getObject());
        } else if (op == L"==") {
            left->setBool(false);
        } else if (op == L"!=") {
            left->setBool(true);
        }

    }

}
