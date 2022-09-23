
#include "../../../../include/joiner/string/string/StringStringJoiner.h"

StringStringJoiner::StringStringJoiner() : Joiner({})
{}

void StringStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
