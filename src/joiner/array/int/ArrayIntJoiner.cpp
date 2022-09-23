
#include "../../../../include/joiner/array/int/ArrayIntJoiner.h"

ArrayIntJoiner::ArrayIntJoiner() : Joiner({})
{}

void ArrayIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
