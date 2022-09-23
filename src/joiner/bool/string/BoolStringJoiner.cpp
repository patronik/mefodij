
#include "../../../../include/joiner/bool/string/BoolStringJoiner.h"

BoolStringJoiner::BoolStringJoiner() : Joiner({})
{}

void BoolStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
