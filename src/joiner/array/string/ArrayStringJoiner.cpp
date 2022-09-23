
#include "../../../../include/joiner/array/string/ArrayStringJoiner.h"

ArrayStringJoiner::ArrayStringJoiner() : Joiner({})
{}

void ArrayStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
}
