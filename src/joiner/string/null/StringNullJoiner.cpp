
#include "../../../../include/joiner/string/null/StringNullJoiner.h"

void StringNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
