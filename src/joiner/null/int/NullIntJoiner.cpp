
#include "../../../../include/joiner/null/int/NullIntJoiner.h"

namespace Mefodij {

    NullIntJoiner::NullIntJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void NullIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVar()->setInt(right->getInt());
            left->setInt(right->getInt());
        } else if (op == L"==") {
            left->setBool(false);
        } else if (op == L"!=") {
            left->setBool(true);
        } 
    }

}
