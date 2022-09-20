
#include "../../../../include/joiner/cast/double/CastDoubleJoiner.h"

void CastDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
