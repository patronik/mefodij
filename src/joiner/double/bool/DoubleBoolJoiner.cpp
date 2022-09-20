
#include "../../../../include/joiner/double/bool/DoubleBoolJoiner.h"

void DoubleBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
