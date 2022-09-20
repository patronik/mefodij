
#include "../../../../include/joiner/int/cast/IntCastJoiner.h"

void IntCastJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
