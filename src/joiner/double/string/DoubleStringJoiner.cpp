
#include "../../../../include/joiner/double/string/DoubleStringJoiner.h"

namespace Mefodij {

    DoubleStringJoiner::DoubleStringJoiner(): Joiner({L"+", L"=", L"==", L"!="})
    {}

    void DoubleStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"+") {
            left->setString(
                Tools::to_wstring(left->getDouble()) + right->getString()
            );
        } else if (op == L"=") {
            left->getVarRef()->setString(right->getString());
            left->setString(right->getString());
        } else if (op == L"==") {
            left->setBool(
                Tools::to_wstring(left->getDouble()) == right->getString()
            );
        } else if (op == L"!=") {
            left->setBool(
                Tools::to_wstring(left->getDouble()) != right->getString()
            );
        } 
    }

}
