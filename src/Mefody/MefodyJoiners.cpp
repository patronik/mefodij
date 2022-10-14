
#include "../../include/Mefody.h"

unique_ptr<BoolBoolJoiner> Mefody::boolBoolJoiner = make_unique<BoolBoolJoiner>();
unique_ptr<BoolIntJoiner> Mefody::boolIntJoiner = make_unique<BoolIntJoiner>();
unique_ptr<BoolNullJoiner> Mefody::boolNullJoiner = make_unique<BoolNullJoiner>();
unique_ptr<BoolArrayJoiner> Mefody::boolArrayJoiner = make_unique<BoolArrayJoiner>();
unique_ptr<BoolDoubleJoiner> Mefody::boolDoubleJoiner = make_unique<BoolDoubleJoiner>();
unique_ptr<BoolStringJoiner> Mefody::boolStringJoiner = make_unique<BoolStringJoiner>();
unique_ptr<IntBoolJoiner> Mefody::intBoolJoiner = make_unique<IntBoolJoiner>();
unique_ptr<IntIntJoiner> Mefody::intIntJoiner = make_unique<IntIntJoiner>();
unique_ptr<IntNullJoiner> Mefody::intNullJoiner = make_unique<IntNullJoiner>();
unique_ptr<IntArrayJoiner> Mefody::intArrayJoiner = make_unique<IntArrayJoiner>();
unique_ptr<IntDoubleJoiner> Mefody::intDoubleJoiner = make_unique<IntDoubleJoiner>();
unique_ptr<IntStringJoiner> Mefody::intStringJoiner = make_unique<IntStringJoiner>();
unique_ptr<NullBoolJoiner> Mefody::nullBoolJoiner = make_unique<NullBoolJoiner>();
unique_ptr<NullIntJoiner> Mefody::nullIntJoiner = make_unique<NullIntJoiner>();
unique_ptr<NullNullJoiner> Mefody::nullNullJoiner = make_unique<NullNullJoiner>();
unique_ptr<NullArrayJoiner> Mefody::nullArrayJoiner = make_unique<NullArrayJoiner>();
unique_ptr<NullDoubleJoiner> Mefody::nullDoubleJoiner = make_unique<NullDoubleJoiner>();
unique_ptr<NullStringJoiner> Mefody::nullStringJoiner = make_unique<NullStringJoiner>();
unique_ptr<ArrayBoolJoiner> Mefody::arrayBoolJoiner = make_unique<ArrayBoolJoiner>();
unique_ptr<ArrayIntJoiner> Mefody::arrayIntJoiner = make_unique<ArrayIntJoiner>();
unique_ptr<ArrayNullJoiner> Mefody::arrayNullJoiner = make_unique<ArrayNullJoiner>();
unique_ptr<ArrayArrayJoiner> Mefody::arrayArrayJoiner = make_unique<ArrayArrayJoiner>();
unique_ptr<ArrayDoubleJoiner> Mefody::arrayDoubleJoiner = make_unique<ArrayDoubleJoiner>();
unique_ptr<ArrayStringJoiner> Mefody::arrayStringJoiner = make_unique<ArrayStringJoiner>();
unique_ptr<DoubleBoolJoiner> Mefody::doubleBoolJoiner = make_unique<DoubleBoolJoiner>();
unique_ptr<DoubleIntJoiner> Mefody::doubleIntJoiner = make_unique<DoubleIntJoiner>();
unique_ptr<DoubleNullJoiner> Mefody::doubleNullJoiner = make_unique<DoubleNullJoiner>();
unique_ptr<DoubleArrayJoiner> Mefody::doubleArrayJoiner = make_unique<DoubleArrayJoiner>();
unique_ptr<DoubleDoubleJoiner> Mefody::doubleDoubleJoiner = make_unique<DoubleDoubleJoiner>();
unique_ptr<DoubleStringJoiner> Mefody::doubleStringJoiner = make_unique<DoubleStringJoiner>();
unique_ptr<StringBoolJoiner> Mefody::stringBoolJoiner = make_unique<StringBoolJoiner>();
unique_ptr<StringIntJoiner> Mefody::stringIntJoiner = make_unique<StringIntJoiner>();
unique_ptr<StringNullJoiner> Mefody::stringNullJoiner = make_unique<StringNullJoiner>();
unique_ptr<StringArrayJoiner> Mefody::stringArrayJoiner = make_unique<StringArrayJoiner>();
unique_ptr<StringDoubleJoiner> Mefody::stringDoubleJoiner = make_unique<StringDoubleJoiner>();
unique_ptr<StringStringJoiner> Mefody::stringStringJoiner = make_unique<StringStringJoiner>();

void Mefody::joinAtoms(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{   
    if (left->getType() == L"int" && right->getType() == L"int") {
        Mefody::intIntJoiner->join(left, op, right);
    } else if (left->getType() == L"int" && right->getType() == L"double") {
        Mefody::intDoubleJoiner->join(left, op, right);
    } else if (left->getType() == L"int" && right->getType() == L"string") {
        Mefody::intStringJoiner->join(left, op, right);
    } else if (left->getType() == L"int" && right->getType() == L"array") {
        Mefody::intArrayJoiner->join(left, op, right);
    } else if (left->getType() == L"int" && right->getType() == L"bool") {
        Mefody::intBoolJoiner->join(left, op, right);
    } else if (left->getType() == L"int" && right->getType() == L"null") {
        Mefody::intNullJoiner->join(left, op, right);
    } else if (left->getType() == L"double" && right->getType() == L"int") {
        Mefody::doubleIntJoiner->join(left, op, right);
    } else if (left->getType() == L"double" && right->getType() == L"double") {
        Mefody::doubleDoubleJoiner->join(left, op, right);
    } else if (left->getType() == L"double" && right->getType() == L"string") {
        Mefody::doubleStringJoiner->join(left, op, right);
    } else if (left->getType() == L"double" && right->getType() == L"array") {
        Mefody::doubleArrayJoiner->join(left, op, right);
    } else if (left->getType() == L"double" && right->getType() == L"bool") {
        Mefody::doubleBoolJoiner->join(left, op, right);
    } else if (left->getType() == L"double" && right->getType() == L"null") {
        Mefody::doubleNullJoiner->join(left, op, right);
    } else if (left->getType() == L"string" && right->getType() == L"int") {
        Mefody::stringIntJoiner->join(left, op, right);
    } else if (left->getType() == L"string" && right->getType() == L"double") {
        Mefody::stringDoubleJoiner->join(left, op, right);
    } else if (left->getType() == L"string" && right->getType() == L"string") {
        Mefody::stringStringJoiner->join(left, op, right);
    } else if (left->getType() == L"string" && right->getType() == L"array") {
        Mefody::stringArrayJoiner->join(left, op, right);
    } else if (left->getType() == L"string" && right->getType() == L"bool") {
        Mefody::stringBoolJoiner->join(left, op, right);
    } else if (left->getType() == L"string" && right->getType() == L"null") {
        Mefody::stringNullJoiner->join(left, op, right);
    } else if (left->getType() == L"array" && right->getType() == L"int") {
        Mefody::arrayIntJoiner->join(left, op, right);
    } else if (left->getType() == L"array" && right->getType() == L"double") {
        Mefody::arrayDoubleJoiner->join(left, op, right);
    } else if (left->getType() == L"array" && right->getType() == L"string") {
        Mefody::arrayStringJoiner->join(left, op, right);
    } else if (left->getType() == L"array" && right->getType() == L"array") {
        Mefody::arrayArrayJoiner->join(left, op, right);
    } else if (left->getType() == L"array" && right->getType() == L"bool") {
        Mefody::arrayBoolJoiner->join(left, op, right);
    } else if (left->getType() == L"array" && right->getType() == L"null") {
        Mefody::arrayNullJoiner->join(left, op, right);
    } else if (left->getType() == L"bool" && right->getType() == L"int") {
        Mefody::boolIntJoiner->join(left, op, right);
    } else if (left->getType() == L"bool" && right->getType() == L"double") {
        Mefody::boolDoubleJoiner->join(left, op, right);
    } else if (left->getType() == L"bool" && right->getType() == L"string") {
        Mefody::boolStringJoiner->join(left, op, right);
    } else if (left->getType() == L"bool" && right->getType() == L"array") {
        Mefody::boolArrayJoiner->join(left, op, right);
    } else if (left->getType() == L"bool" && right->getType() == L"bool") {
        Mefody::boolBoolJoiner->join(left, op, right);
    } else if (left->getType() == L"bool" && right->getType() == L"null") {
        Mefody::boolNullJoiner->join(left, op, right);
    } else if (left->getType() == L"null" && right->getType() == L"int") {
        Mefody::nullIntJoiner->join(left, op, right);
    } else if (left->getType() == L"null" && right->getType() == L"double") {
        Mefody::nullDoubleJoiner->join(left, op, right);
    } else if (left->getType() == L"null" && right->getType() == L"string") {
        Mefody::nullStringJoiner->join(left, op, right);
    } else if (left->getType() == L"null" && right->getType() == L"array") {
        Mefody::nullArrayJoiner->join(left, op, right);
    } else if (left->getType() == L"null" && right->getType() == L"bool") {
        Mefody::nullBoolJoiner->join(left, op, right);
    } else if (left->getType() == L"null" && right->getType() == L"null") {
        Mefody::nullNullJoiner->join(left, op, right);
    } else {
        throw runtime_error(
            "Joiner for type " + wideStrToStr(left->getType())
            + " operator " + wideStrToStr(op)
            + " and type " + wideStrToStr(right->getType())
            + " does not exist."
        );   
    }    
}

void Mefody::assignToAtom(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    if (!left->getVar()) {
        throw runtime_error("Assignment can only be done to variable");                    
    } 
    joinAtoms(left, L"=", right);
}