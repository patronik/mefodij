
#include "../../../../include/joiner/cast/int/CastIntJoiner.h"

void CastIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
