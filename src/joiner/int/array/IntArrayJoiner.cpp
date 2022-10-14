
#include "../../../../include/joiner/int/array/IntArrayJoiner.h"

IntArrayJoiner::IntArrayJoiner() : Joiner({L"в", L"="})
{}

void IntArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"в") {
        bool found = false;
        for (const auto & kv : right->getArray()) {
            if (kv.second->getType() == Atom::typeInt) {
                if (kv.second->getInt() == left->getInt()) {
                    found = true;
                    break;
                }
            }
        }
        left->setBool(found);
    } else if (op == L"=") { 
        left->getVar()->setArray(right->getArray());
        left->setArray(right->getArray());
    }
}
