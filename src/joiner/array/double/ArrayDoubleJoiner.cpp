
#include "../../../../include/joiner/array/double/ArrayDoubleJoiner.h"

ArrayDoubleJoiner::ArrayDoubleJoiner() : Joiner({})
{}

void ArrayDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
