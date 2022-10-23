
#include "../../../../include/joiner/double/string/DoubleStringJoiner.h"

DoubleStringJoiner::DoubleStringJoiner(): Joiner({L"+"})
{
}

void DoubleStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"+") {
        left->setString(
            to_wstring(left->getDouble()) + right->getString()
        );
    }
}
