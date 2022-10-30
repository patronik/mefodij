
#include "../../../../include/joiner/string/double/StringDoubleJoiner.h"

namespace Mefody {

    StringDoubleJoiner::StringDoubleJoiner() : Joiner({L"+", L"="})
    {}

    void StringDoubleJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"+") {
            left->setString(
                left->getString() + to_wstring(right->getDouble())
            );
        } else if (op == L"=") {
            if (left->getCharIndex() > -1) {
                throw new runtime_error("Cannot assign non string value to string character");
            }
            
            left->getVar()->setString(to_wstring(right->getDouble()));
        }
    }

}
