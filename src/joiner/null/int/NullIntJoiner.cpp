
#include "../../../../include/joiner/null/int/NullIntJoiner.h"

NullIntJoiner::NullIntJoiner() : Joiner({L"="})
{}

void NullIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"=") {
        left->getVar()->setInt(right->getInt());
        left->setInt(right->getInt());
    }
}
