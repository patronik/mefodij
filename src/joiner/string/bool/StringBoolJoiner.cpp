
#include "../../../../include/joiner/string/bool/StringBoolJoiner.h"

StringBoolJoiner::StringBoolJoiner() : Joiner({})
{}

void StringBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
