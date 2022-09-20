
#include "../../../../include/joiner/null/double/NullDoubleJoiner.h"

void NullDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
