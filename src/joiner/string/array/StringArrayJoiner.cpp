
#include "../../../../include/joiner/string/array/StringArrayJoiner.h"

StringArrayJoiner::StringArrayJoiner() : Joiner({L"in"})
{}

void StringArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"in") {
        bool found = false;
        for (const auto & kv : right->getArray()) {
            if (kv.second->getType() == Atom::typeString) {
                if (kv.second->getString() == left->getString()) {
                    found = true;
                    break;
                }
            }
        }
        left->setBool(found);
    }
}
