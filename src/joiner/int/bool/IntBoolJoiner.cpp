
#include "../../../../include/joiner/int/bool/IntBoolJoiner.h"

void IntBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
