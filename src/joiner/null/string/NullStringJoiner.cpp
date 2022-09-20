
#include "../../../../include/joiner/null/string/NullStringJoiner.h"

void NullStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
