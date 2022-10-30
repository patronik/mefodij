
#include "../../../../include/joiner/null/null/NullNullJoiner.h"

namespace Mefody {

    NullNullJoiner::NullNullJoiner() : Joiner({L"="})
    {}

    void NullNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);
    }

}
