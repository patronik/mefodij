
#include "../../../../include/joiner/int/array/IntArrayJoiner.h"

namespace Mefodij {

    IntArrayJoiner::IntArrayJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void IntArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"==") { 
            left->setBool(false);
        } else if (op == L"!=") { 
            left->setBool(true);
        } else if (op == L"=") { 
            left->getVar()->setArray(right->getArray());
            left->setArray(right->getArray());
        }
    }

}
