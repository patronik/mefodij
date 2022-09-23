
#include "../../../../include/joiner/bool/double/BoolDoubleJoiner.h"

BoolDoubleJoiner::BoolDoubleJoiner() : Joiner({})
{}

void BoolDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
