
#include "../../../../include/joiner/array/bool/ArrayBoolJoiner.h"

ArrayBoolJoiner::ArrayBoolJoiner() : Joiner({})
{}

void ArrayBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
