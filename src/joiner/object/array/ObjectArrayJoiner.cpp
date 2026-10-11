#include "../../../../include/joiner/object/array/ObjectArrayJoiner.h"

namespace Mefodij {

    ObjectArrayJoiner::ObjectArrayJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void ObjectArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVarRef()->setArray(right->getArray());
            left->setArray(right->getArray());
        } else if (op == L"==") {
            left->setBool(false);
        } else if (op == L"!=") {
            left->setBool(true);
        }

    }

}
