
#include "../../../../include/joiner/double/bool/DoubleBoolJoiner.h"

namespace Mefody {

    DoubleBoolJoiner::DoubleBoolJoiner() : Joiner({L"==", L"||", L"&&", L"="})
    {
    }

    void DoubleBoolJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        validate(op);

        if (op == L"==") {
            left->setBool(
                (bool) (left->getDouble()) == right->getBool()
            );
        } else if (op == L"||") {
            left->setBool(
                (bool) (left->getDouble()) || right->getBool()
            );
        } else if (op == L"&&") {
            left->setBool(
                (bool) (left->getDouble()) && right->getBool()
            );
        } else if (op == L"=") {
            left->getVar()->setDouble((int)right->getBool());
        }
    }

}
