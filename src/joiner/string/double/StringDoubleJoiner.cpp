
#include "../../../../include/joiner/string/double/StringDoubleJoiner.h"

StringDoubleJoiner::StringDoubleJoiner() : Joiner({})
{}

void StringDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
