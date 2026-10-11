#include "../../../../include/joiner/null/object/NullObjectJoiner.h"

namespace Mefodij {

    NullObjectJoiner::NullObjectJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void NullObjectJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
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
