
#include "../../../../include/joiner/double/cast/DoubleCastJoiner.h"

DoubleCastJoiner::DoubleCastJoiner() : Joiner({L"cast"})
{
}

void DoubleCastJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (left->getCast() == L"int") {
        right->setInt((int) right->getDouble());
    } else if (left->getCast() == L"string") {
        right->setString(to_wstring(right->getDouble()));
    } else if (left->getCast() == L"bool") {
        right->setBool((bool) right->getDouble());
    } else if (left->getCast() == L"null") {
        right->setNull();
    } else if (left->getCast() == L"array") {
        right->setArray({{L"0", make_shared<Atom>(right->getDouble())}});
    }
}
