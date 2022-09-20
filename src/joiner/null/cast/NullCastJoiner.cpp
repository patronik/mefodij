
#include "../../../../include/joiner/null/cast/NullCastJoiner.h"

void NullCastJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
