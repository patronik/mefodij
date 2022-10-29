
#include "../../../../include/joiner/string/array/StringArrayJoiner.h"

StringArrayJoiner::StringArrayJoiner() : Joiner({L"="})
{}

void StringArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"=") { 
        left->getVar()->setArray(right->getArray());
    }
}
