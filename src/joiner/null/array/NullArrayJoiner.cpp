
#include "../../../../include/joiner/null/array/NullArrayJoiner.h"

NullArrayJoiner::NullArrayJoiner() : Joiner({L"=", L"in"})
{}

void NullArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"=") {
        if (!left->getVar()) {
            throw runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setArray(right->getArray());
        left->setArray(right->getArray());
    } else if (op == L"in") {
        bool found = false;
        for (const auto & kv : right->getArray()) {
            if (kv.second->getType() == Atom::typeNull) {
                found = true;
                break;
            }
        }
        left->setBool(found);
    }
}
