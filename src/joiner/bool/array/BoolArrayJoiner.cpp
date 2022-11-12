
#include "../../../../include/joiner/bool/array/BoolArrayJoiner.h"

namespace Mefodij {

    BoolArrayJoiner::BoolArrayJoiner() : Joiner({L"=", L"=="})
    {}

    void BoolArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVarRef()->setArray(right->getArray());
            left->setArray(right->getArray());
        } else if (op == L"==") {
            left->setBool(
                left->getBool() == !right->getArray().empty()
            );
        }
    }

}