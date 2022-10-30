
#include "../../../../include/joiner/string/bool/StringBoolJoiner.h"

namespace Mefody {

    StringBoolJoiner::StringBoolJoiner() : Joiner({L"==", L"||", L"&&", L"="})
    {}

    void StringBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"==") {
            left->setBool(
                (bool) (left->getString().size() > 0) == right->getBool()
            );
        } else if (op == L"||") {
            left->setBool(
                (bool) (left->getString().size() > 0) || right->getBool()
            );
        } else if (op == L"&&") {
            left->setBool(
                (bool) (left->getString().size() > 0) && right->getBool()
            );
        } else if (op == L"=") { 
            if (left->getCharIndex() > -1) {
                throw new runtime_error("Cannot assign non string value to string character");
            }
            
            left->getVar()->setBool(right->getBool());
        }
    }

}
