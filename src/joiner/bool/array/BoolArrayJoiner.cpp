
#include "../../../../include/joiner/bool/array/BoolArrayJoiner.h"

BoolArrayJoiner::BoolArrayJoiner() : Joiner({L"in"})
{}

void BoolArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"in") {
        bool found = false;
        for (const auto & kv : right->getArray()) {
            if (kv.second->getType() == Atom::typeBool) {
                if (kv.second->getBool() == left->getBool()) {
                    found = true;
                    break;
                }
            }
        }
        left->setBool(found);
    }
}
