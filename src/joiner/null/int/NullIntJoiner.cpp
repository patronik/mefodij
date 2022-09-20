
#include "../../../../include/joiner/null/int/NullIntJoiner.h"

void NullIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
