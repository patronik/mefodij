#include "../../../../include/joiner/object/bool/ObjectBoolJoiner.h"

namespace Mefodij {

    ObjectBoolJoiner::ObjectBoolJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void ObjectBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVarRef()->setBool(right->getBool());
            left->setBool(right->getBool());
        } else if (op == L"==") {
            left->setBool(
                !left->getObject().empty() == right->getBool()
            );
        } else if (op == L"!=") {
            left->setBool(
                !left->getObject().empty() != right->getBool()
            );
        }

    }

}
