#include "../../../../include/joiner/object/int/ObjectIntJoiner.h"

namespace Mefodij {

    ObjectIntJoiner::ObjectIntJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void ObjectIntJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVarRef()->setInt(right->getInt());
            left->setInt(right->getInt());
        } else if (op == L"==") {
            left->setBool(false);
        } else if (op == L"!=") {
            left->setBool(true);
        }

    }

}
