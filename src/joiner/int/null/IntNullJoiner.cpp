
#include "../../../../include/joiner/int/null/IntNullJoiner.h"

void IntNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
