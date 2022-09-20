
#include "../../../../include/joiner/int/cast/IntCastJoiner.h"

IntCastJoiner::IntCastJoiner() : Joiner({L"cast"})
{}

void IntCastJoiner::join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    validate(op);

    if (left->getCast() == L"double") {
        right->setDouble((double) right->getInt());
    } else if (left->getCast() == L"string") {
        right->setString(to_wstring(right->getInt()));
    } else if (left->getCast() == L"bool") {
        right->setBool((bool) right->getInt());
    } else if (left->getCast() == L"null") {
        right->setNull();
    } else if (left->getCast() == L"array") {
        right->setArray({{L"0", make_shared<Atom>(right->getInt())}});
    }
}
