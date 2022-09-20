
#include "../../../../include/joiner/cast/bool/CastBoolJoiner.h"

void CastBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
