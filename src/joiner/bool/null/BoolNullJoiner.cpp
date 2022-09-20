
#include "../../../../include/joiner/bool/null/BoolNullJoiner.h"

void BoolNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
