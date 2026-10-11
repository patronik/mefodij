#include "../../../../include/joiner/object/double/ObjectDoubleJoiner.h"

namespace Mefodij {

    ObjectDoubleJoiner::ObjectDoubleJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void ObjectDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVarRef()->setDouble(right->getDouble());
            left->setDouble(right->getDouble());
        } else if (op == L"==") {
            left->setBool(false);
        } else if (op == L"!=") {
            left->setBool(true);
        }

    }

}
