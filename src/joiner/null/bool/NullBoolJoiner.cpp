
#include "../../../../include/joiner/null/bool/NullBoolJoiner.h"

void NullBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
