
#include "../../../../include/joiner/double/array/DoubleArrayJoiner.h"

DoubleArrayJoiner::DoubleArrayJoiner() : Joiner({L"in"})
{
}

void DoubleArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"in") {
        bool found = false;
        for (const auto & kv : right->getArray()) {
            if (kv.second->getType() == Atom::typeDouble) {
                if (kv.second->getDouble() == left->getDouble()) {
                    found = true;
                    break;
                }
            }
        }
        left->setBool(found);
    }
}
