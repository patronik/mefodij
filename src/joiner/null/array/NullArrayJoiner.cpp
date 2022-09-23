
#include "../../../../include/joiner/null/array/NullArrayJoiner.h"

NullArrayJoiner::NullArrayJoiner() : Joiner({})
{}

void NullArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
