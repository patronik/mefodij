
#include "../../../../include/joiner/int/string/IntStringJoiner.h"

IntStringJoiner::IntStringJoiner(): Joiner({L"."})
{
}

void IntStringJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);
    
    if (op == L".") {
        left->setString(
            to_wstring(left->getInt()) + right->getString()
        );
    }
}
