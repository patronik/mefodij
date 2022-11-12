
#include "../../../../include/joiner/string/array/StringArrayJoiner.h"

namespace Mefodij {

    StringArrayJoiner::StringArrayJoiner() : Joiner({L"=", L"==", L"!="})
    {}

    void StringArrayJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"=") { 
            left->getVarRef()->setArray(right->getArray());
            left->setArray(right->getArray());
        } else if (op == L"==") { 
            left->setBool(false);
        } else if (op == L"!=") { 
            left->setBool(true);
        }
    }

}