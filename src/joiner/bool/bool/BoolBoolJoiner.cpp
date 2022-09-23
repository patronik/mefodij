
#include "../../../../include/joiner/bool/bool/BoolBoolJoiner.h"

BoolBoolJoiner::BoolBoolJoiner() : Joiner({})
{}

void BoolBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
