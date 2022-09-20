
#include "../../../../include/joiner/double/cast/DoubleCastJoiner.h"

void DoubleCastJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
