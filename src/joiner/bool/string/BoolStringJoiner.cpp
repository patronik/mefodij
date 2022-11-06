
#include "../../../../include/joiner/bool/string/BoolStringJoiner.h"

namespace Mefodij {

    BoolStringJoiner::BoolStringJoiner() : Joiner({L"=", L"+"})
    {}

    void BoolStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"+") {
            left->getVar()->setString(left->toString() + right->getString());
            left->setString(left->toString() + right->getString());
        } else if (op == L"=") {
            left->getVar()->setBool(right->getString() != L"");
            left->setBool(right->getString() != L"");
        }
    }

}