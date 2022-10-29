#include "../include/Atom/AtomType.h"
#include "../include/Atom.h"
#include "../include/tools.h"

Atom::Atom()
{
    type = L"null";
    initMembers();
}

Atom::Atom(long val) 
{
   type = L"int";
   intVal = val;
   initMembers();
}


Atom::Atom(double val) 
{
   type = L"double";
   doubleVal = val;
   initMembers();
}

Atom::Atom(wstring val) 
{
   type = L"string";
   stringVal = val;
   initMembers();
}


Atom::Atom(map<wstring, shared_ptr<Atom>> val) 
{
   type = L"array";
   arrayVal = val;
   initMembers();
}

Atom::Atom(bool val) 
{
   type = L"bool";
   boolVal = val;
   initMembers();
}

int Atom::getArrayNextIndex()
{
    return arrayNextIndex;
}

void Atom::setArrayNextIndex(const int index)
{
    arrayNextIndex = index;
}

int Atom::getCharIndex()
{
    return charIndex;
}

void Atom::setCharIndex(const int index)
{
    charIndex = index;
}

void Atom::setVar(shared_ptr<Atom> atom)
{
    varRef = atom;
}

shared_ptr<Atom> Atom::getVar()
{
    return varRef;
}

wstring Atom::getType()
{
    return type;
}

void Atom::clearVal() 
{ 
    options = 0;
    intVal = 0;  
    doubleVal = 0.0;
    stringVal.clear();
    arrayVal.clear();
    boolVal = false;
    castVal.clear();
    arrayNextIndex = 0;
    charIndex = -1;
}

void Atom::setInt(long val) 
{
    clearVal();
    intVal = val;
    type = AtomType::typeInt;        
}

void Atom::setDouble(double val) 
{
    clearVal();
    doubleVal = val;
    type = AtomType::typeDouble;        
}

void Atom::setString(wstring val) 
{
    clearVal();
    stringVal = val;
    type = AtomType::typeString;        
}

void Atom::setStringChar(wchar_t val, int charIndex)
{
    stringVal[charIndex] = val;
}

void Atom::setArray(map<wstring, shared_ptr<Atom>> val) 
{
    clearVal();
    arrayVal = val;
    type = AtomType::typeArray; 
    
    if (arrayVal.size() > 0) {
        int topIndex = 0;
        for (auto elem: arrayVal) {
            try {
                if (MefodyTools::isNumber(elem.first)) {
                    int i = stoi(elem.first);
                    if (i > topIndex) {
                        topIndex = i;
                    }
                }
            } catch (...) {
                throw runtime_error("Unknown error while setting array.");
            }
        }
        setArrayNextIndex(topIndex + 1);   
    } else {
        setArrayNextIndex(0);
    }
}

void Atom::setBool(bool val) 
{
    clearVal();
    boolVal = val;
    type = AtomType::typeBool;        
}

void Atom::setNull() 
{
    clearVal();
    type = AtomType::typeNull;        
}

void Atom::setCast(wstring val) 
{
    clearVal();
    castVal = val;
    type = AtomType::typeCast;        
}

long Atom::getInt() 
{
    if (type != AtomType::typeInt) {
        throw runtime_error("Wrong atom type");
    }
    return intVal;
}

double Atom::getDouble() 
{
    if (type != AtomType::typeDouble) {
        throw runtime_error("Wrong atom type");
    }
    return doubleVal;
}

wstring Atom::getString() 
{
    if (type != AtomType::typeString) {
        throw runtime_error("Wrong atom type");
    }
    return stringVal;
}

map<wstring, shared_ptr<Atom>> Atom::getArray() 
{
    if (type != AtomType::typeArray) {
        throw runtime_error("Wrong atom type");
    }
    return arrayVal;
}  

bool Atom::getBool() 
{
    if (type != AtomType::typeBool) {
        throw runtime_error("Wrong atom type");
    }
    return boolVal;
}

wstring Atom::getCast() 
{
    if (type != AtomType::typeCast) {
        throw runtime_error("Wrong atom type");
    }
    return castVal;
} 

bool Atom::issetAt(wstring key)
{
    if (type != AtomType::typeArray) {
        throw runtime_error("Method is not supported by non array atom");
    }

    if (arrayVal.count(key)) {
       return true;
    } 
    return false;
}

shared_ptr<Atom> Atom::elementAt(wstring key)
{
    if (type != AtomType::typeArray) {
        throw runtime_error("Method is not supported by non array atom");
    }

    if (!arrayVal.count(key)) {
        throw runtime_error("Element with key " + string(key.begin(), key.end()) + " does not exist");
    }

    return arrayVal.at(key);
}

void Atom::createAt(wstring key, shared_ptr<Atom> val) 
{
    if (type != AtomType::typeArray) {
        throw runtime_error("Method is not supported by non array atom");
    }

    arrayVal.insert(pair<wstring, shared_ptr<Atom>>{key, val});
}

bool Atom::toBool()
{
    if (type == AtomType::typeInt) {
        return intVal > 0;
    }
    if (type == AtomType::typeDouble ) {
        return doubleVal > 0;
    }
    if (type == AtomType::typeString ) {
        return !stringVal.empty();
    }
    if (type == AtomType::typeArray) {
        return arrayVal.size() > 0;
    }
    if (type == AtomType::typeBool) {
        return boolVal;
    }
    if (type == AtomType::typeNull) {
        return false;
    }
    if (type == AtomType::typeCast ) {
        return !castVal.empty();
    }
    throw runtime_error("Not supported atom type");
}

wstring Atom::toString() 
{
    if (type == AtomType::typeInt) {
        return to_wstring(intVal);
    }
    if (type == AtomType::typeDouble ) {
        return to_wstring(doubleVal);
    }
    if (type == AtomType::typeString ) {
        return stringVal;
    }
    if (type == AtomType::typeArray) {
        wstring str;
        for (auto elem: arrayVal) {
            str += elem.second->toString();
        }
        return str;
    }
    if (type == AtomType::typeBool) {
        return boolVal ? L"true" : L"false";
    }
    if (type == AtomType::typeCast) {
        throw runtime_error("Cast to string conversion");
    }
    if (type == AtomType::typeNull) {
        return L"";
    }
    throw runtime_error("Not supported atom type");
}

void Atom::preOperator(wstring op)
{
    if (varRef != nullptr) {
        varRef->preOperator(op);
    }

    if (op == L"++") {
        if (type == AtomType::typeInt) {
            ++intVal;
        } else if (type == AtomType::typeDouble) {
            ++doubleVal;
        } else {
            throw runtime_error("Pre increment is not supported by type " + string(type.begin(), type.end()));
        }
    } else if (op == L"--") {
        if (type == AtomType::typeInt) {
            --intVal;
        } else if (type == AtomType::typeDouble) {
            --doubleVal;
        } else {
            throw runtime_error("Pre decrement is not supported by type " + string(type.begin(), type.end()));
        }
    } else if (op == L"!") {
        if (type == AtomType::typeInt) {
            setBool(!((bool) intVal));
        } else if (type == AtomType::typeDouble) {
            setBool(!((bool) doubleVal));
        } else if (type == AtomType::typeBool) {
            setBool(!(boolVal));
        } else {
            throw runtime_error("Boolean inversion is not supported by type " + string(type.begin(), type.end()));
        }
    } else {
        throw runtime_error("Not supported pre operator " + string(op.begin(), op.end()));
    }
}

void Atom::postOperator(wstring op)
{
    if (varRef != nullptr) {
        varRef->postOperator(op);
    }

    if (op == L"++") {
        if (type == AtomType::typeInt) {
            intVal++;
        } else if (type == AtomType::typeDouble) {
            doubleVal++;
        } else {
            throw runtime_error("Post increment is not supported by type " + string(type.begin(), type.end()));
        }
    } else if (op == L"--") {
        if (type == AtomType::typeInt) {
            intVal--;
        } else if (type == AtomType::typeDouble) {
            doubleVal--;
        } else {
            throw runtime_error("Post decrement is not supported by type " + string(type.begin(), type.end()));
        }
    } else {
        throw runtime_error("Not supported post operator " + string(op.begin(), op.end()));
    }
}

void Atom::unaryOperator(wstring op)
{
    if (varRef != nullptr) {
        varRef->unaryOperator(op);
    }

    if (op == L"+") {
        if (type == AtomType::typeInt) {
            +intVal;
        } else if (type == AtomType::typeDouble) {
            -doubleVal;
        } else {
            throw runtime_error(
                "Unary operator " + string(op.begin(), op.end()) 
                + " is not supported by type " 
                + string(type.begin(), type.end())
            );
        }
    } else if (op == L"-") {
        if (type == AtomType::typeInt) {
            -intVal;
        } else if (type == AtomType::typeDouble) {
            -doubleVal;
        } else {
            throw runtime_error(
                "Unary operator " + string(op.begin(), op.end()) 
                + " is not supported by type " 
                + string(type.begin(), type.end())
            );
        }
    } else {
        throw runtime_error("Not supported unary operator " + string(op.begin(), op.end()));
    }
}

void Atom::cast(wstring typeTo)
{
    if (type == AtomType::typeString) {
        if (typeTo == AtomType::castString) {
            return;
        } else if (typeTo == AtomType::castInt) {
            setInt(wcstol(getString().c_str(), nullptr, 10));
        } else if (typeTo == AtomType::castDouble) {
            setDouble(wcstod(getString().c_str(), nullptr));
        } else if (typeTo == AtomType::castBool) {
            setBool(getString() != L"");
        } else if (typeTo == AtomType::castArray) {
            int i = 0;
            map<wstring, shared_ptr<Atom>> arrayVal;
            while (i < getString().size()) {
                arrayVal[to_wstring(i)] = make_shared<Atom>(
                    wstring(1, getString().at(i))
                );
                i++;
            }
            setArray(arrayVal);
        } else if (typeTo == AtomType::castNull) {
            setNull();
        } else {
            throw runtime_error("Cast failed.");
        }
    }

    if (type == AtomType::typeArray) {
        if (typeTo == AtomType::castArray) {
            return;
        } else if (typeTo == AtomType::castString) {
            wstring stringVal;
            for (auto elem: arrayVal) {
                stringVal += elem.second->toString();
            }
            setString(stringVal);
        } else {
            throw runtime_error("Cast failed.");
        }
    }

    if (type == AtomType::typeBool) {
        if (typeTo == AtomType::castBool) {
            return;
        } else if (typeTo == AtomType::castInt) {
            setInt((int) getBool());
        } else if (typeTo == AtomType::castString) {
            if (getBool()) {
                setString(L"true");
            } else {
                setString(L"false");
            }
        } else if (typeTo == AtomType::castDouble) {
            setDouble((double) getBool());
        } else if (typeTo == AtomType::castNull) {
            setNull();
        } else {
            throw runtime_error("Cast failed.");
        }
    }

    if (type == AtomType::typeInt) {
        if (typeTo == AtomType::castInt) {
            return;
        } else if (typeTo == AtomType::castString) {
            setString(to_wstring(getInt()));
        } else if (typeTo == AtomType::castDouble) {
            setDouble((double) getInt());
        } else if (typeTo == AtomType::castBool) {
            setBool((bool) getInt());
        } else if (typeTo == AtomType::castNull) {
            setNull();
        } else {
            throw runtime_error("Cast failed.");
        }
    }

    if (type == AtomType::typeDouble) {
        if (typeTo == AtomType::castDouble) {
            return;
        } else if (typeTo == AtomType::castInt) {
            setInt((int) getDouble());
        } else if (typeTo == AtomType::castString) {
            setString(to_wstring(getDouble()));
        } else if (typeTo == AtomType::castBool) {
            setBool((bool) getDouble());
        } else if (typeTo == AtomType::castNull) {
            setNull();
        } else {
            throw runtime_error("Cast failed.");
        }
    }

    if (type == AtomType::typeNull) {
        if (typeTo == AtomType::castNull) {
            return;
        } else {
            setNull();
        }
    }
}

void Atom::setAtom(const Atom & src)
{
    *this = src;
}

bool Atom::getIsConst()
{
    return options[0] == true;
}

bool Atom::getIsAssigned()
{
    return options[1] == true;
}

bool Atom::getIsCalculated()
{
    return options[2] == true;
}

void Atom::setIsConst()
{
    options[0] = true;
}

void Atom::setIsAssigned()
{
    options[1] = true;
}

void Atom::setIsCalculated()
{
    options[2] = true;
}

void Atom::initMembers()
{
    members = {
        {
            L"string", {
                {L"довжина", &Atom::resolveStringSize}
            }
        },
        {
            L"array", {
                {L"розмір", &Atom::resolveArraySize},
                {L"перший", &Atom::resolveArrayFirst},
                {L"другий", &Atom::resolveArraySecond}
            }
        }
    };
}

void Atom::resolveStringSize()
{
    setInt(stringVal.size());
    setVar(nullptr);
    setIsCalculated();
}

void Atom::resolveArraySize()
{
    setInt(arrayVal.size());
    setVar(nullptr);
    setIsCalculated();
}

void Atom::resolveArrayFirst()
{
    if (getVar() != nullptr) {
        auto varRef = getVar();
        if (varRef->getArray().size() < 1) {
            throw runtime_error("First element of array does not exist.");
        }
        setAtom(*(varRef->getArray().begin()->second));
        setVar(varRef->getArray().begin()->second);
    } else {
        if (arrayVal.size() < 1) {
            throw runtime_error("First element of array does not exist.");
        }
        setAtom(*(arrayVal.begin()->second));
        setVar(nullptr);
    }
}

void Atom::resolveArraySecond()
{
    if (getVar() != nullptr) {
        auto varRef = getVar();
        if (varRef->getArray().size() < 2) {
            throw runtime_error("Second element of array does not exist.");
        }
        setAtom(*((++(varRef->getArray().begin()))->second));
        setVar((++(varRef->getArray().begin()))->second);
    } else {
        if (arrayVal.size() < 2) {
            throw runtime_error("Second element of array does not exist.");
        }
        setAtom(*((++(arrayVal.begin()))->second));
        setVar(nullptr);
    }
}

void Atom::resolveMember(wstring name)
{
    if (!members.count(type)) {
        throw runtime_error(
            "Atom of type '" 
            + MefodyTools::wideStrToStr(type) 
            + "' does not have members."
        );
    }

    if (!members[type].count(name)) {
        throw runtime_error(
            "Atom of type '" 
            + MefodyTools::wideStrToStr(type) 
            + "' does not have a member '" 
            + MefodyTools::wideStrToStr(name) 
            + "'."
        );
    }

    (this->*members[type][name])();
}