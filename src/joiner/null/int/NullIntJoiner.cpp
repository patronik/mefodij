
#include "../../../../include/joiner/null/int/NullIntJoiner.h"

namespace Mefody {

    NullIntJoiner::NullIntJoiner() : Joiner({L"="})
    {}

    void NullIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVar()->setInt(right->getInt());
        }
    }

}
