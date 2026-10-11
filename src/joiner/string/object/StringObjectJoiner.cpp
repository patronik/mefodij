#include "../../../../include/joiner/string/object/StringObjectJoiner.h"

namespace Mefodij {

    StringObjectJoiner::StringObjectJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void StringObjectJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") {
            left->getVarRef()->setObject(right->getObject());
            left->setObject(right->getObject());
        } else if (op == L"==") {
            left->setBool(false);
        } else if (op == L"!=") {
            left->setBool(true);
        }

    }

}
