
#include "../../../../include/joiner/array/bool/ArrayBoolJoiner.h"

namespace Mefodij {

    ArrayBoolJoiner::ArrayBoolJoiner() : Joiner({L"=", L"=="})
    {}

    void ArrayBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);
        if (op == L"=") {
            left->getVarRef()->setBool(right->getBool());
            left->setBool(right->getBool());
        } else if (op == L"==") {
            left->setBool(
                !left->getArray().empty() == right->getBool()
            );
        } 
    }

}