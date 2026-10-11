#include "../../../../include/joiner/bool/object/BoolObjectJoiner.h"

namespace Mefodij {

    BoolObjectJoiner::BoolObjectJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void BoolObjectJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVarRef()->setObject(right->getObject());
            left->setObject(right->getObject());
        } else if (op == L"==") {
            left->setBool(
                left->getBool() == !right->getObject().empty()
            );
        } else if (op == L"!=") {
            left->setBool(
                left->getBool() != !right->getObject().empty()
            );
        }

    }

}
