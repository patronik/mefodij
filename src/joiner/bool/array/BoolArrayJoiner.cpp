
#include "../../../../include/joiner/bool/array/BoolArrayJoiner.h"

BoolArrayJoiner::BoolArrayJoiner() : Joiner({})
{}

void BoolArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
