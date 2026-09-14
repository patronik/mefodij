
#include "../../../../include/joiner/double/null/DoubleNullJoiner.h"

namespace Mefodij {

    DoubleNullJoiner::DoubleNullJoiner() : Joiner({L"=", L"==", L"!=", L"+", L"-", L"*", L"/", L"%"})
    {}

    void DoubleNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"+") {
            left->setDouble(left->getDouble() + 0.0);
        } else if (op == L"-") {
            left->setDouble(left->getDouble() - 0.0);
        } else if (op == L"*") {
            left->setDouble(0.0);
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
