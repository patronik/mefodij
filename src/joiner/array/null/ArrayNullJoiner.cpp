
#include "../../../../include/joiner/array/null/ArrayNullJoiner.h"

ArrayNullJoiner::ArrayNullJoiner() : Joiner({L"="})
{}

void ArrayNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"=") {
        left->getVar()->setNull();
        left->setNull(); 
    }
}
