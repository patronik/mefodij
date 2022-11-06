
#include "../../../../include/joiner/null/double/NullDoubleJoiner.h"

namespace Mefodij {

    NullDoubleJoiner::NullDoubleJoiner() : Joiner({L"="})
    {}

    void NullDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") { 
            left->getVar()->setDouble(right->getDouble());
            left->setDouble(right->getDouble());
        }
    }

}
