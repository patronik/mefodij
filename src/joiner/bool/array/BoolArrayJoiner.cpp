
#include "../../../../include/joiner/bool/array/BoolArrayJoiner.h"

BoolArrayJoiner::BoolArrayJoiner() : Joiner({L"в", L"="})
{}

void BoolArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"в") {
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
    } else if (op == L"=") {
        if (!left->getVar()) {
            throw runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setArray(right->getArray());
        left->setArray(right->getArray());
    }
}
