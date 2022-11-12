
#include "../../../../include/joiner/double/array/DoubleArrayJoiner.h"

namespace Mefodij {

    DoubleArrayJoiner::DoubleArrayJoiner() : Joiner({L"=", L"==", L"!="})
    {
    }

    void DoubleArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"==") { 
            left->setBool(false);
        } else if (op == L"!=") { 
            left->setBool(true);
        } else if (op == L"=") { 
            left->getVarRef()->setArray(right->getArray());
            left->setArray(right->getArray());
        }
    }

}
