
#include "../../../../include/joiner/bool/double/BoolDoubleJoiner.h"

void BoolDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
