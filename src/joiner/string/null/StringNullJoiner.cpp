
#include "../../../../include/joiner/string/null/StringNullJoiner.h"

namespace Mefody {

    StringNullJoiner::StringNullJoiner() : Joiner({L"=", L"+"})
    {}

    void StringNullJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);
        if (op == L"+") {
            
        } else if (op == L"=") {
            if (left->getCharIndex() > -1) {
                throw new runtime_error("Cannot assign non string value to string character");
            }

            left->getVar()->setNull();
            left->setNull();
        }
    }

}
