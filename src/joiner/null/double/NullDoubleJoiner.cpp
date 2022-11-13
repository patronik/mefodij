
#include "../../../../include/joiner/null/double/NullDoubleJoiner.h"

namespace Mefodij {

    NullDoubleJoiner::NullDoubleJoiner() : Joiner({L"=", L"==", L"!=", L"+", L"-"})
    {}

    void NullDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"+") {
            left->setDouble(0.00 + right->getDouble());
        } if (op == L"-") {
            left->setDouble(0.00 - right->getDouble());
        } else if (op == L"=") { 
            left->getVarRef()->setDouble(right->getDouble());
            left->setDouble(right->getDouble());
        } else if (op == L"==") {
            left->setBool(false);
        } else if (op == L"!=") {
            left->setBool(true);
        } 
    }

}
