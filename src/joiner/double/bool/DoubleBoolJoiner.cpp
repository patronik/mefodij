
#include "../../../../include/joiner/double/bool/DoubleBoolJoiner.h"

DoubleBoolJoiner::DoubleBoolJoiner() : Joiner({L"==", L"||", L"&&", L"="})
{
}

void DoubleBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (op == L"==") {
        left->setBool(
            (bool) (left->getDouble()) == right->getBool()
        );
    } else if (op == L"||") {
        left->setBool(
            (bool) (left->getDouble()) || right->getBool()
        );
    } else if (op == L"&&") {
         left->setBool(
            (bool) (left->getDouble()) && right->getBool()
        );
    } else if (op == L"=") {
        if (!left->getVar()) {
            throw new runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setDouble((int)right->getBool());
        left->setDouble((int)right->getBool()); 
    }
}
