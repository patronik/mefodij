
#include "../../../../include/joiner/null/array/NullArrayJoiner.h"

void NullArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
