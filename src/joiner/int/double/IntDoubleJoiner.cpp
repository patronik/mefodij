
#include "../../../../include/joiner/int/double/IntDoubleJoiner.h"

IntDoubleJoiner::IntDoubleJoiner(): Joiner({L"==", L"||", L"&&", L"="})
{
}

void IntDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
    
    if (op == L"==") {
        left->setBool(
             left->getInt() == ((int) right->getDouble())
        );
    } else if (op == L"||") {
        left->setBool(
            left->getInt() || ((int) right->getDouble())
        );
    } else if (op == L"&&") {
         left->setBool(
            left->getInt() && ((int) right->getDouble())
        );
    } else if (op == L"=") {
        if (!left->getVar()) {
            throw runtime_error("Assignment can only be done to variable");                    
        } 
        left->getVar()->setInt((int)right->getDouble());
        left->setInt((int)right->getDouble()); 
    }
}
