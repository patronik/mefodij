
#include "../../include/Engine.h"
#include "../../include/Atom/AtomType.h"

namespace Mefody {

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
        if (left->getType() == AtomType::typeInt && right->getType() == AtomType::typeInt) {
            Engine::intIntJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeInt && right->getType() == AtomType::typeDouble) {
            Engine::intDoubleJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeInt && right->getType() == AtomType::typeString) {
            Engine::intStringJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeInt && right->getType() == AtomType::typeArray) {
            Engine::intArrayJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeInt && right->getType() == AtomType::typeBool) {
            Engine::intBoolJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeInt && right->getType() == AtomType::typeNull) {
            Engine::intNullJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeDouble && right->getType() == AtomType::typeInt) {
            Engine::doubleIntJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeDouble && right->getType() == AtomType::typeDouble) {
            Engine::doubleDoubleJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeDouble && right->getType() == AtomType::typeString) {
            Engine::doubleStringJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeDouble && right->getType() == AtomType::typeArray) {
            Engine::doubleArrayJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeDouble && right->getType() == AtomType::typeBool) {
            Engine::doubleBoolJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeDouble && right->getType() == AtomType::typeNull) {
            Engine::doubleNullJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeString && right->getType() == AtomType::typeInt) {
            Engine::stringIntJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeString && right->getType() == AtomType::typeDouble) {
            Engine::stringDoubleJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeString && right->getType() == AtomType::typeString) {
            Engine::stringStringJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeString && right->getType() == AtomType::typeArray) {
            Engine::stringArrayJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeString && right->getType() == AtomType::typeBool) {
            Engine::stringBoolJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeString && right->getType() == AtomType::typeNull) {
            Engine::stringNullJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeArray && right->getType() == AtomType::typeInt) {
            Engine::arrayIntJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeArray && right->getType() == AtomType::typeDouble) {
            Engine::arrayDoubleJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeArray && right->getType() == AtomType::typeString) {
            Engine::arrayStringJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeArray && right->getType() == AtomType::typeArray) {
            Engine::arrayArrayJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeArray && right->getType() == AtomType::typeBool) {
            Engine::arrayBoolJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeArray && right->getType() == AtomType::typeNull) {
            Engine::arrayNullJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeBool && right->getType() == AtomType::typeInt) {
            Engine::boolIntJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeBool && right->getType() == AtomType::typeDouble) {
            Engine::boolDoubleJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeBool && right->getType() == AtomType::typeString) {
            Engine::boolStringJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeBool && right->getType() == AtomType::typeArray) {
            Engine::boolArrayJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeBool && right->getType() == AtomType::typeBool) {
            Engine::boolBoolJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeBool && right->getType() == AtomType::typeNull) {
            Engine::boolNullJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeNull && right->getType() == AtomType::typeInt) {
            Engine::nullIntJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeNull && right->getType() == AtomType::typeDouble) {
            Engine::nullDoubleJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeNull && right->getType() == AtomType::typeString) {
            Engine::nullStringJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeNull && right->getType() == AtomType::typeArray) {
            Engine::nullArrayJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeNull && right->getType() == AtomType::typeBool) {
            Engine::nullBoolJoiner->join(left, op, right);
        } else if (left->getType() == AtomType::typeNull && right->getType() == AtomType::typeNull) {
            Engine::nullNullJoiner->join(left, op, right);
        } else {
            throw runtime_error(
                "Joiner for type " + Mefody::Tools::wideStrToStr(left->getType())
                + " operator " + Mefody::Tools::wideStrToStr(op)
                + " and type " + Mefody::Tools::wideStrToStr(right->getType())
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

        if (left->getIsConst() && left->getIsAssigned()) {
            throw runtime_error("Cannot change the value of const variable."); 
        }

        joinAtoms(left, L"=", right);

        if (!left->getIsAssigned()) {
            left->getVar()->setIsAssigned();
        }
    }

}