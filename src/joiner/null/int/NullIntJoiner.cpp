
#include "../../../../include/joiner/null/int/NullIntJoiner.h"

NullIntJoiner::NullIntJoiner() : Joiner({})
{}

void NullIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
