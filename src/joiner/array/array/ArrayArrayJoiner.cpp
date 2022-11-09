
#include "../../../../include/joiner/array/array/ArrayArrayJoiner.h"

namespace Mefodij {

    ArrayArrayJoiner::ArrayArrayJoiner() : Joiner({L"=", L"==",  L"!="})
    {}

    void ArrayArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);
        if (op == L"=") {
            left->getVar()->setArray(right->getArray());
            left->setArray(right->getArray());
        } else if (op == L"==") {
            if (left->getArray().size() != right->getArray().size()) {
                left->setBool(false);
            } else {
                left->setBool(
                    left->getArray() == right->getArray()
                );
            }
        } else if (op == L"!=") {
            if (left->getArray().size() != right->getArray().size()) {
                left->setBool(true);
            } else {
                left->setBool(
                    left->getArray() != right->getArray()
                );
            }
        } 
    }

}