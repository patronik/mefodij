
#include "../../../../include/joiner/null/double/NullDoubleJoiner.h"

NullDoubleJoiner::NullDoubleJoiner() : Joiner({})
{}

void NullDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
