
#include "../../../../include/joiner/int/null/IntNullJoiner.h"

namespace Mefodij {

    IntNullJoiner::IntNullJoiner() : Joiner({L"=", L"==", L"!=", L"+", L"-", L"*", L"/", L"%"})
    {}

    void IntNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"+") {
            left->setInt(left->getInt() + 0);
        } else if (op == L"-") {
            left->setInt(left->getInt() - 0);
        } else if (op == L"*") {
            left->setInt(0);
        } else if (op == L"/" || op == L"%") {
            throw runtime_error("Division by zero.");
        } else if (op == L"=") {
            left->getVarRef()->setNull();
            left->setNull();
        } else if (op == L"==") {
            left->setBool(false);
        } else if (op == L"!=") {
            left->setBool(true);
        } 
    }

}
