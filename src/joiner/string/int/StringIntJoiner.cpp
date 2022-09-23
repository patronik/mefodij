
#include "../../../../include/joiner/string/int/StringIntJoiner.h"

StringIntJoiner::StringIntJoiner() : Joiner({})
{}

void StringIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
