
#include "../../../../include/joiner/array/double/ArrayDoubleJoiner.h"

namespace Mefodij {

    ArrayDoubleJoiner::ArrayDoubleJoiner() : Joiner({L"=", L"=="})
    {}

    void ArrayDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);
        if (op == L"=") {
            left->getVar()->setDouble(right->getDouble());
            left->setDouble(right->getDouble());
        } else if (op == L"==") {
            left->setBool(false);
        }
    }

}