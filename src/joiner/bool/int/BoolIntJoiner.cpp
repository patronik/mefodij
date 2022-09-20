
#include "../../../../include/joiner/bool/int/BoolIntJoiner.h"

void BoolIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
