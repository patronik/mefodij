
#include "../../../../include/joiner/cast/null/CastNullJoiner.h"

void CastNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
