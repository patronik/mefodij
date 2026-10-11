#include "../../../../include/joiner/object/object/ObjectObjectJoiner.h"

namespace Mefodij {

    ObjectObjectJoiner::ObjectObjectJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void ObjectObjectJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVarRef()->setObject(right->getObject());
            left->setObject(right->getObject());
        } else if (op == L"==") {
            if (left->getObject().size() != right->getObject().size()) {
                left->setBool(false);
            } else {
                left->setBool(
                    left->getObject() == right->getObject()
                );
            }
        } else if (op == L"!=") {
            if (left->getObject().size() != right->getObject().size()) {
                left->setBool(true);
            } else {
                left->setBool(
                    left->getObject() != right->getObject()
                );
            }
        }

    }

}
