#include "../include/Atom/Keyword.h"
#include "../include/Atom.h"
#include "../include/tools.h"
namespace Mefodij {

    Atom::Atom()
    {
        type = Keyword::typeNull;
        initMembers();
    }

    Atom::Atom(long val) 
    {
        type = Keyword::typeInt;
        intVal = val;
        initMembers();
    }


    Atom::Atom(double val) 
    {
        type = Keyword::typeDouble;
        doubleVal = val;
        initMembers();
    }

    Atom::Atom(wstring val) 
    {
        type = Keyword::typeString;
        stringVal = val;
        initMembers();
    }


    Atom::Atom(map<wstring, shared_ptr<Atom>, Tools::arrayCmp> val) 
    {
        type = Keyword::typeArray;
        arrayVal = val;
        initMembers();
    }

    Atom::Atom(bool val) 
    {
        type = Keyword::typeBool;
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
        type = Keyword::typeInt;        
    }

    void Atom::setDouble(double val) 
    {
        clearVal();
        doubleVal = val;
        type = Keyword::typeDouble;        
    }

    void Atom::setString(wstring val) 
    {
        clearVal();
        stringVal = val;
        type = Keyword::typeString;        
    }

    void Atom::setStringChar(wchar_t val, int charIndex)
    {
        stringVal[charIndex] = val;
    }

    void Atom::setArray(map<wstring, shared_ptr<Atom>, Tools::arrayCmp> val) 
    {
        clearVal();
        arrayVal = val;
        type = Keyword::typeArray; 
        
        if (arrayVal.size() > 0) {
            int topIndex = 0;
            for (auto elem: arrayVal) {
                try {
                    if (Mefodij::Tools::isNumber(elem.first)) {
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
        type = Keyword::typeBool;        
    }

    void Atom::setNull() 
    {
        clearVal();
        type = Keyword::typeNull;        
    }

    void Atom::setCast(wstring val) 
    {
        clearVal();
        castVal = val;
        type = Keyword::typeCast;        
    }

    long Atom::getInt() 
    {
        if (type != Keyword::typeInt) {
            throw runtime_error("Wrong atom type");
        }
        return intVal;
    }

    double Atom::getDouble() 
    {
        if (type != Keyword::typeDouble) {
            throw runtime_error("Wrong atom type");
        }
        return doubleVal;
    }

    wstring Atom::getString() 
    {
        if (type != Keyword::typeString) {
            throw runtime_error("Wrong atom type");
        }
        return stringVal;
    }

    map<wstring, shared_ptr<Atom>, Tools::arrayCmp> Atom::getArray() 
    {
        if (type != Keyword::typeArray) {
            throw runtime_error("Wrong atom type");
        }
        return arrayVal;
    }  

    bool Atom::getBool() 
    {
        if (type != Keyword::typeBool) {
            throw runtime_error("Wrong atom type");
        }
        return boolVal;
    }

    wstring Atom::getCast() 
    {
        if (type != Keyword::typeCast) {
            throw runtime_error("Wrong atom type");
        }
        return castVal;
    } 

    bool Atom::issetAt(wstring key)
    {
        if (type != Keyword::typeArray) {
            throw runtime_error("Method is not supported by non array atom");
        }

        if (arrayVal.count(key)) {
        return true;
        } 
        return false;
    }

    shared_ptr<Atom> Atom::elementAt(wstring key)
    {
        if (type != Keyword::typeArray) {
            throw runtime_error("Method is not supported by non array atom");
        }

        if (!arrayVal.count(key)) {
            throw runtime_error(
                "Element with key '" 
                + Tools::wideStrToStr(key) 
                + "' does not exist"
            );
        }

        return arrayVal.at(key);
    }

    void Atom::createAt(wstring key, shared_ptr<Atom> val) 
    {
        if (type != Keyword::typeArray) {
            throw runtime_error("Method is not supported by non array atom");
        }

        arrayVal.insert(pair<wstring, shared_ptr<Atom>>{key, val});
    }

    bool Atom::toBool()
    {
        if (type == Keyword::typeBool) {
            return boolVal;
        } else if (type == Keyword::typeInt) {
            return intVal != 0;
        } else if (type == Keyword::typeDouble ) {
            return doubleVal != 0;
        } else if (type == Keyword::typeString ) {
            return !stringVal.empty();
        } else if (type == Keyword::typeArray) {
            return !arrayVal.empty();
        } else if (type == Keyword::typeNull) {
            return false;
        } else {
            throw runtime_error(
                "Cannot covert atom of type '" 
                + Tools::wideStrToStr(type) 
                + "' to bool."
            );
        }
    }

    wstring Atom::toString() 
    {
        if (type == Keyword::typeString) {
            return stringVal;
        } else if (type == Keyword::typeInt) {
            return to_wstring(intVal);
        } else if (type == Keyword::typeDouble ) {
            return to_wstring(doubleVal);
        } else if (type == Keyword::typeArray) {
            wstring str;
            for (auto elem: arrayVal) {
                str += elem.second->toString();
            }
            return str;
        } else if (type == Keyword::typeBool) {
            return boolVal 
            ? Keyword::True 
            : Keyword::False;
        } else if (type == Keyword::typeNull) {
            return L"";
        } else {
            throw runtime_error(
                "Cannot covert atom of type '" 
                + Tools::wideStrToStr(type) 
                + "' to string."
            );
        }
    }

    void Atom::preOperator(wstring op)
    {
        if (varRef != nullptr) {
            varRef->preOperator(op);
        }

        if (op == L"++") {
            if (type == Keyword::typeInt) {
                ++intVal;
            } else if (type == Keyword::typeDouble) {
                ++doubleVal;
            } else {
                throw runtime_error(
                    "Pre increment is not supported by type '" 
                    + Tools::wideStrToStr(type) 
                    + "'."
                );
            }
        } else if (op == L"--") {
            if (type == Keyword::typeInt) {
                --intVal;
            } else if (type == Keyword::typeDouble) {
                --doubleVal;
            } else {
                throw runtime_error(
                    "Pre decrement is not supported by type '" 
                    + Tools::wideStrToStr(type) 
                    + "'."
                );
            }
        } else if (op == L"!") {
            if (type == Keyword::typeInt) {
                setBool(!((bool) intVal));
            } else if (type == Keyword::typeDouble) {
                setBool(!((bool) doubleVal));
            } else if (type == Keyword::typeBool) {
                setBool(!(boolVal));
            } else {
                throw runtime_error(
                    "Boolean inversion is not supported by type " 
                    + Tools::wideStrToStr(type) 
                    + "'."
                );
            }
        } else {
            throw runtime_error(
                "Not supported pre operator " 
                + Tools::wideStrToStr(op) 
                + "'."
            );
        }
    }

    void Atom::postOperator(wstring op)
    {
        if (varRef != nullptr) {
            varRef->postOperator(op);
        }

        if (op == L"++") {
            if (type == Keyword::typeInt) {
                intVal++;
            } else if (type == Keyword::typeDouble) {
                doubleVal++;
            } else {
                throw runtime_error(
                    "Post increment is not supported by type '" 
                    + Tools::wideStrToStr(type) 
                    + "'."
                );
            }
        } else if (op == L"--") {
            if (type == Keyword::typeInt) {
                intVal--;
            } else if (type == Keyword::typeDouble) {
                doubleVal--;
            } else {
                throw runtime_error(
                    "Post decrement is not supported by type '" 
                    + Tools::wideStrToStr(type) 
                    + "'."
                );
            }
        } else {
            throw runtime_error(
                "Not supported post operator " 
                + Tools::wideStrToStr(op) 
                + "'."
            );
        }
    }

    void Atom::unaryOperator(wstring op)
    {
        if (varRef != nullptr) {
            varRef->unaryOperator(op);
        }

        if (op == L"+") {
            if (type == Keyword::typeInt) {
                +intVal;
            } else if (type == Keyword::typeDouble) {
                -doubleVal;
            } else {
                throw runtime_error(
                    "Unary operator " + string(op.begin(), op.end()) 
                    + " is not supported by type " 
                    + string(type.begin(), type.end())
                );
            }
        } else if (op == L"-") {
            if (type == Keyword::typeInt) {
                -intVal;
            } else if (type == Keyword::typeDouble) {
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
        if (type == Keyword::typeString) {
            if (typeTo == Keyword::castString) {
                return;
            } else if (typeTo == Keyword::castInt) {
                setInt(wcstol(getString().c_str(), nullptr, 10));
            } else if (typeTo == Keyword::castDouble) {
                setDouble(wcstod(getString().c_str(), nullptr));
            } else if (typeTo == Keyword::castBool) {
                setBool(getString() != L"");
            } else if (typeTo == Keyword::castArray) {
                map<wstring, shared_ptr<Atom>, Tools::arrayCmp> tmpArray; 
                for (int i = 0; i < stringVal.size(); i++) {
                    tmpArray.insert(
                        {to_wstring(i), make_shared<Atom>(wstring(1, stringVal.at(i)))}
                    ); 
                }
                setArray(tmpArray);
            } else {
                throw runtime_error("Cast failed.");
            }
        }

        if (type == Keyword::typeArray) {
            if (typeTo == Keyword::castArray) {
                return;
            } else if (typeTo == Keyword::castString) {
                wstring stringVal;
                for (auto elem: arrayVal) {
                    stringVal += elem.second->toString();
                }
                setString(stringVal);
            } else {
                throw runtime_error("Cast failed.");
            }
        }

        if (type == Keyword::typeBool) {
            if (typeTo == Keyword::castBool) {
                return;
            } else if (typeTo == Keyword::castInt) {
                setInt((int) getBool());
            } else if (typeTo == Keyword::castString) {
                if (getBool()) {
                    setString(Keyword::True);
                } else {
                    setString(Keyword::False);
                }
            } else if (typeTo == Keyword::castDouble) {
                setDouble((double) getBool());
            } else {
                throw runtime_error("Cast failed.");
            }
        }

        if (type == Keyword::typeInt) {
            if (typeTo == Keyword::castInt) {
                return;
            } else if (typeTo == Keyword::castString) {
                setString(to_wstring(getInt()));
            } else if (typeTo == Keyword::castDouble) {
                setDouble((double) getInt());
            } else if (typeTo == Keyword::castBool) {
                setBool((bool) getInt());
            } else {
                throw runtime_error("Cast failed.");
            }
        }

        if (type == Keyword::typeDouble) {
            if (typeTo == Keyword::castDouble) {
                return;
            } else if (typeTo == Keyword::castInt) {
                setInt((int) getDouble());
            } else if (typeTo == Keyword::castString) {
                setString(to_wstring(getDouble()));
            } else if (typeTo == Keyword::castBool) {
                setBool((bool) getDouble());
            } else {
                throw runtime_error("Cast failed.");
            }
        }

        if (type == Keyword::typeNull) {
            throw runtime_error("Cannot cast null.");
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
                    {Keyword::Length, &Atom::resolveStringSize}
                }
            },
            {
                L"array", {
                    {Keyword::Size, &Atom::resolveArraySize},
                    {Keyword::First, &Atom::resolveArrayFirst},
                    {Keyword::Second, &Atom::resolveArraySecond}
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
                + Mefodij::Tools::wideStrToStr(type) 
                + "' does not have members."
            );
        }

        if (!members[type].count(name)) {
            throw runtime_error(
                "Atom of type '" 
                + Mefodij::Tools::wideStrToStr(type) 
                + "' does not have a member '" 
                + Mefodij::Tools::wideStrToStr(name) 
                + "'."
            );
        }

        (this->*members[type][name])();
    }

}