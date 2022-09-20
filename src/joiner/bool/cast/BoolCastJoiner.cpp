
#include "../../../../include/joiner/bool/cast/BoolCastJoiner.h"

void BoolCastJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
