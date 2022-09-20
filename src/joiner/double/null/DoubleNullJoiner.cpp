
#include "../../../../include/joiner/double/null/DoubleNullJoiner.h"

void DoubleNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
