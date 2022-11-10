
#include "../../include/Engine.h"
#include "../../include/Atom/Keyword.h"

namespace Mefodij {

    unique_ptr<BoolBoolJoiner> Engine::boolBoolJoiner = make_unique<BoolBoolJoiner>();
    unique_ptr<BoolIntJoiner> Engine::boolIntJoiner = make_unique<BoolIntJoiner>();
    unique_ptr<BoolNullJoiner> Engine::boolNullJoiner = make_unique<BoolNullJoiner>();
    unique_ptr<BoolArrayJoiner> Engine::boolArrayJoiner = make_unique<BoolArrayJoiner>();
    unique_ptr<BoolDoubleJoiner> Engine::boolDoubleJoiner = make_unique<BoolDoubleJoiner>();
    unique_ptr<BoolStringJoiner> Engine::boolStringJoiner = make_unique<BoolStringJoiner>();
    unique_ptr<IntBoolJoiner> Engine::intBoolJoiner = make_unique<IntBoolJoiner>();
    unique_ptr<IntIntJoiner> Engine::intIntJoiner = make_unique<IntIntJoiner>();
    unique_ptr<IntNullJoiner> Engine::intNullJoiner = make_unique<IntNullJoiner>();
    unique_ptr<IntArrayJoiner> Engine::intArrayJoiner = make_unique<IntArrayJoiner>();
    unique_ptr<IntDoubleJoiner> Engine::intDoubleJoiner = make_unique<IntDoubleJoiner>();
    unique_ptr<IntStringJoiner> Engine::intStringJoiner = make_unique<IntStringJoiner>();
    unique_ptr<NullBoolJoiner> Engine::nullBoolJoiner = make_unique<NullBoolJoiner>();
    unique_ptr<NullIntJoiner> Engine::nullIntJoiner = make_unique<NullIntJoiner>();
    unique_ptr<NullNullJoiner> Engine::nullNullJoiner = make_unique<NullNullJoiner>();
    unique_ptr<NullArrayJoiner> Engine::nullArrayJoiner = make_unique<NullArrayJoiner>();
    unique_ptr<NullDoubleJoiner> Engine::nullDoubleJoiner = make_unique<NullDoubleJoiner>();
    unique_ptr<NullStringJoiner> Engine::nullStringJoiner = make_unique<NullStringJoiner>();
    unique_ptr<ArrayBoolJoiner> Engine::arrayBoolJoiner = make_unique<ArrayBoolJoiner>();
    unique_ptr<ArrayIntJoiner> Engine::arrayIntJoiner = make_unique<ArrayIntJoiner>();
    unique_ptr<ArrayNullJoiner> Engine::arrayNullJoiner = make_unique<ArrayNullJoiner>();
    unique_ptr<ArrayArrayJoiner> Engine::arrayArrayJoiner = make_unique<ArrayArrayJoiner>();
    unique_ptr<ArrayDoubleJoiner> Engine::arrayDoubleJoiner = make_unique<ArrayDoubleJoiner>();
    unique_ptr<ArrayStringJoiner> Engine::arrayStringJoiner = make_unique<ArrayStringJoiner>();
    unique_ptr<DoubleBoolJoiner> Engine::doubleBoolJoiner = make_unique<DoubleBoolJoiner>();
    unique_ptr<DoubleIntJoiner> Engine::doubleIntJoiner = make_unique<DoubleIntJoiner>();
    unique_ptr<DoubleNullJoiner> Engine::doubleNullJoiner = make_unique<DoubleNullJoiner>();
    unique_ptr<DoubleArrayJoiner> Engine::doubleArrayJoiner = make_unique<DoubleArrayJoiner>();
    unique_ptr<DoubleDoubleJoiner> Engine::doubleDoubleJoiner = make_unique<DoubleDoubleJoiner>();
    unique_ptr<DoubleStringJoiner> Engine::doubleStringJoiner = make_unique<DoubleStringJoiner>();
    unique_ptr<StringBoolJoiner> Engine::stringBoolJoiner = make_unique<StringBoolJoiner>();
    unique_ptr<StringIntJoiner> Engine::stringIntJoiner = make_unique<StringIntJoiner>();
    unique_ptr<StringNullJoiner> Engine::stringNullJoiner = make_unique<StringNullJoiner>();
    unique_ptr<StringArrayJoiner> Engine::stringArrayJoiner = make_unique<StringArrayJoiner>();
    unique_ptr<StringDoubleJoiner> Engine::stringDoubleJoiner = make_unique<StringDoubleJoiner>();
    unique_ptr<StringStringJoiner> Engine::stringStringJoiner = make_unique<StringStringJoiner>();

    void Engine::joinAtoms(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {   
        if (left->getType() == Keyword::typeInt && right->getType() == Keyword::typeInt) {
            Engine::intIntJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeInt && right->getType() == Keyword::typeDouble) {
            Engine::intDoubleJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeInt && right->getType() == Keyword::typeString) {
            Engine::intStringJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeInt && right->getType() == Keyword::typeArray) {
            Engine::intArrayJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeInt && right->getType() == Keyword::typeBool) {
            Engine::intBoolJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeInt && right->getType() == Keyword::typeNull) {
            Engine::intNullJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeDouble && right->getType() == Keyword::typeInt) {
            Engine::doubleIntJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeDouble && right->getType() == Keyword::typeDouble) {
            Engine::doubleDoubleJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeDouble && right->getType() == Keyword::typeString) {
            Engine::doubleStringJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeDouble && right->getType() == Keyword::typeArray) {
            Engine::doubleArrayJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeDouble && right->getType() == Keyword::typeBool) {
            Engine::doubleBoolJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeDouble && right->getType() == Keyword::typeNull) {
            Engine::doubleNullJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeString && right->getType() == Keyword::typeInt) {
            Engine::stringIntJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeString && right->getType() == Keyword::typeDouble) {
            Engine::stringDoubleJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeString && right->getType() == Keyword::typeString) {
            Engine::stringStringJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeString && right->getType() == Keyword::typeArray) {
            Engine::stringArrayJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeString && right->getType() == Keyword::typeBool) {
            Engine::stringBoolJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeString && right->getType() == Keyword::typeNull) {
            Engine::stringNullJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeArray && right->getType() == Keyword::typeInt) {
            Engine::arrayIntJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeArray && right->getType() == Keyword::typeDouble) {
            Engine::arrayDoubleJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeArray && right->getType() == Keyword::typeString) {
            Engine::arrayStringJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeArray && right->getType() == Keyword::typeArray) {
            Engine::arrayArrayJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeArray && right->getType() == Keyword::typeBool) {
            Engine::arrayBoolJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeArray && right->getType() == Keyword::typeNull) {
            Engine::arrayNullJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeBool && right->getType() == Keyword::typeInt) {
            Engine::boolIntJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeBool && right->getType() == Keyword::typeDouble) {
            Engine::boolDoubleJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeBool && right->getType() == Keyword::typeString) {
            Engine::boolStringJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeBool && right->getType() == Keyword::typeArray) {
            Engine::boolArrayJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeBool && right->getType() == Keyword::typeBool) {
            Engine::boolBoolJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeBool && right->getType() == Keyword::typeNull) {
            Engine::boolNullJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeNull && right->getType() == Keyword::typeInt) {
            Engine::nullIntJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeNull && right->getType() == Keyword::typeDouble) {
            Engine::nullDoubleJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeNull && right->getType() == Keyword::typeString) {
            Engine::nullStringJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeNull && right->getType() == Keyword::typeArray) {
            Engine::nullArrayJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeNull && right->getType() == Keyword::typeBool) {
            Engine::nullBoolJoiner->join(left, op, right);
        } else if (left->getType() == Keyword::typeNull && right->getType() == Keyword::typeNull) {
            Engine::nullNullJoiner->join(left, op, right);
        } else {
            throw runtime_error(
                "Joiner for type " + Mefodij::Tools::wideStrToStr(left->getType())
                + " operator " + Mefodij::Tools::wideStrToStr(op)
                + " and type " + Mefodij::Tools::wideStrToStr(right->getType())
                + " does not exist."
            );   
        }    
    }

    void Engine::assignToAtom(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
    {
        if (left->getIsCalculated()) {
            throw runtime_error("Cannot assign to dynamicaly calculated value."); 
        }

        if (!left->getVar()) {
            throw runtime_error("Assignment can only be done to variable.");                    
        } 

        if (left->getVar()->getIsConst() && left->getVar()->getIsAssigned()) {
            throw runtime_error("Cannot change the value of const variable."); 
        }

        joinAtoms(left, L"=", right);

        if (!left->getVar()->getIsAssigned()) {
            left->getVar()->setIsAssigned();
        }
    }

}