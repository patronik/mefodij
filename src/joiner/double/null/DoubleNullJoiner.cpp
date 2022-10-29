
#include "../../../../include/joiner/double/null/DoubleNullJoiner.h"

DoubleNullJoiner::DoubleNullJoiner() : Joiner({L"="})
{}

void DoubleNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"=") { 
        left->getVar()->setNull();
    }
}
