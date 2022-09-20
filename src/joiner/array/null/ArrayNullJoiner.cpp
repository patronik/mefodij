
#include "../../../../include/joiner/array/null/ArrayNullJoiner.h"

void ArrayNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
