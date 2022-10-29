
#include "../../../../include/joiner/bool/string/BoolStringJoiner.h"

BoolStringJoiner::BoolStringJoiner() : Joiner({L"="})
{}

void BoolStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"=") {
        left->getVar()->setBool(right->getString().size() > 0);
    }
}
