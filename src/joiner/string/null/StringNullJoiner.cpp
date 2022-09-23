
#include "../../../../include/joiner/string/null/StringNullJoiner.h"

StringNullJoiner::StringNullJoiner() : Joiner({})
{}

void StringNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
