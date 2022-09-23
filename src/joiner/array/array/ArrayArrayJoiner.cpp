
#include "../../../../include/joiner/array/array/ArrayArrayJoiner.h"

ArrayArrayJoiner::ArrayArrayJoiner() : Joiner({})
{}

void ArrayArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
