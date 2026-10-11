#include "../../../../include/joiner/object/string/ObjectStringJoiner.h"

namespace Mefodij {

    ObjectStringJoiner::ObjectStringJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void ObjectStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVarRef()->setString(right->getString());
            left->setString(right->getString());
        } else if (op == L"==") {
            left->setBool(false);
        } else if (op == L"!=") {
            left->setBool(true);
        }

    }

}
