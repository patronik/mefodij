#include "../include/Atom/Keyword.h"
#include "../include/Atom.h"
#include "../include/tools.h"
namespace Mefodij {

    Atom::Atom(void * nullPtr, wstring sT)
    {
        type = Keyword::typeNull;
        storageType = sT;
        initMembers();
    }

    Atom::Atom(long val, wstring sT) 
    {
        type = Keyword::typeInt;
        storageType = sT;
        intVal = val;
        initMembers();
    }


    Atom::Atom(double val, wstring sT) 
    {
        type = Keyword::typeDouble;
        storageType = sT;
        doubleVal = val;
        initMembers();
    }

    Atom::Atom(wstring val, wstring sT) 
    {
        type = Keyword::typeString;
        storageType = sT;
        stringVal = val;
        initMembers();
    }


    Atom::Atom(map<wstring, shared_ptr<Atom>, Tools::arrayCmp> val, wstring sT) 
    {
        type = Keyword::typeArray;
        storageType = sT;
        arrayVal = val;
        initMembers();
    }

    Atom::Atom(bool val, wstring sT) 
    {
        type = Keyword::typeBool;
        storageType = sT;
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

    void Atom::setVarRef(shared_ptr<Atom> atom)
    {
        varRef = atom;
    }

    shared_ptr<Atom> Atom::getVarRef()
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
                    if (Tools::isNumber(elem.first)) {
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

    bool Atom::issetAt(wstring key)
    {
        if (type != Keyword::typeArray) {
            throw runtime_error("Method is not supported by non array.");
        }

        if (arrayVal.count(key)) {
        return true;
        } 
        return false;
    }

    shared_ptr<Atom> Atom::elementAt(wstring key)
    {
        if (type != Keyword::typeArray) {
            throw runtime_error("Method is not supported by non array.");
        }

        if (!arrayVal.count(key)) {
            throw runtime_error(
                "Element with key '" + Tools::wideStrToStr(key) + "' does not exist"
            );
        }

        return arrayVal.at(key);
    }

    void Atom::setElementAt(wstring key, shared_ptr<Atom> val) 
    {
        if (type != Keyword::typeArray) {
            throw runtime_error("Method is not supported by non array.");
        }

        val->setKey(key);
        val->setIsArrayElem();

        arrayVal[key] = val;
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
            return Tools::to_wstring(intVal);
        } else if (type == Keyword::typeDouble ) {
            return Tools::to_wstring(doubleVal);
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
            if (typeTo == Keyword::typeString) {
                return;
            } else if (typeTo == Keyword::typeInt) {
                setInt(wcstol(getString().c_str(), nullptr, 10));
            } else if (typeTo == Keyword::typeDouble) {
                setDouble(wcstod(getString().c_str(), nullptr));
            } else if (typeTo == Keyword::typeBool) {
                setBool(getString() != L"");
            } else if (typeTo == Keyword::typeArray) {
                map<wstring, shared_ptr<Atom>, Tools::arrayCmp> tmpArray; 
                for (int i = 0; i < stringVal.size(); i++) {
                    tmpArray.insert(
                        {Tools::to_wstring(i), make_shared<Atom>(wstring(1, stringVal.at(i)))}
                    ); 
                }
                setArray(tmpArray);
            } else if (typeTo == Keyword::typeNull) {
                setNull();
            } else {
                throw runtime_error(
                    "Cannot cast type '" 
                    + Tools::wideStrToStr(type) 
                    + "' to type '" 
                    + Tools::wideStrToStr(typeTo) 
                    + "'."
                );
            }
        }

        if (type == Keyword::typeArray) {
            if (typeTo == Keyword::typeArray) {
                return;
            } else if (typeTo == Keyword::typeString) {
                wstring stringVal;
                for (auto elem: arrayVal) {
                    stringVal += elem.second->toString();
                }
                setString(stringVal);
            } else if (typeTo == Keyword::typeNull) {
                setNull();
            } else {
                throw runtime_error(
                    "Cannot cast type '" 
                    + Tools::wideStrToStr(type) 
                    + "' to type '" 
                    + Tools::wideStrToStr(typeTo) 
                    + "'."
                );
            }
        }

        if (type == Keyword::typeBool) {
            if (typeTo == Keyword::typeBool) {
                return;
            } else if (typeTo == Keyword::typeInt) {
                setInt((int) getBool());
            } else if (typeTo == Keyword::typeString) {
                if (getBool()) {
                    setString(Keyword::True);
                } else {
                    setString(Keyword::False);
                }
            } else if (typeTo == Keyword::typeDouble) {
                setDouble((double) getBool());
            } else if (typeTo == Keyword::typeNull) {
                setNull();
            } else {
                throw runtime_error(
                    "Cannot cast type '" 
                    + Tools::wideStrToStr(type) 
                    + "' to type '" 
                    + Tools::wideStrToStr(typeTo) 
                    + "'."
                );
            }
        }

        if (type == Keyword::typeInt) {
            if (typeTo == Keyword::typeInt) {
                return;
            } else if (typeTo == Keyword::typeString) {
                setString(Tools::to_wstring(getInt()));
            } else if (typeTo == Keyword::typeDouble) {
                setDouble((double) getInt());
            } else if (typeTo == Keyword::typeBool) {
                setBool((bool) getInt());
            } else if (typeTo == Keyword::typeNull) {
                setNull();
            } else {
                throw runtime_error(
                    "Cannot cast type '" 
                    + Tools::wideStrToStr(type) 
                    + "' to type '" 
                    + Tools::wideStrToStr(typeTo) 
                    + "'."
                );
            }
        }

        if (type == Keyword::typeDouble) {
            if (typeTo == Keyword::typeDouble) {
                return;
            } else if (typeTo == Keyword::typeInt) {
                setInt((int) getDouble());
            } else if (typeTo == Keyword::typeString) {
                setString(Tools::to_wstring(getDouble()));
            } else if (typeTo == Keyword::typeBool) {
                setBool((bool) getDouble());
            } else if (typeTo == Keyword::typeNull) {
                setNull();
            } else {
                throw runtime_error(
                    "Cannot cast type '" 
                    + Tools::wideStrToStr(type) 
                    + "' to type '" 
                    + Tools::wideStrToStr(typeTo) 
                    + "'."
                );
            }
        }

        if (type == Keyword::typeNull) {
            if (typeTo == Keyword::typeNull) {
                return;
            } else if (typeTo == Keyword::typeBool) {
                setBool(false);
            } else {
                throw runtime_error(
                    "Cannot cast type '" 
                    + Tools::wideStrToStr(type) 
                    + "' to type '" 
                    + Tools::wideStrToStr(typeTo) 
                    + "'."
                );
            }
        }
    }

    void Atom::setAtom(const Atom & src)
    {
    
        if (src.type == Keyword::typeInt) {
            setInt(src.intVal);
        } else if (src.type == Keyword::typeDouble) {
            setDouble(src.doubleVal);
        } else if (src.type == Keyword::typeBool) {
            setBool(src.boolVal);
        } else if (src.type == Keyword::typeArray) {
            setArray(src.arrayVal);
        } else if (src.type == Keyword::typeString) {
            setString(src.stringVal);
        } else if (src.type == Keyword::typeNull) {
            setNull();
        }

        arrayNextIndex = src.arrayNextIndex;
        charIndex = src.charIndex;
    }

    vector<wstring> Atom::getMemberNames()
    {
        return {
            Keyword::Length,
            Keyword::Size,
            Keyword::Type,
            Keyword::Address,
            Keyword::First,
            Keyword::Second,
        };
    }

    void Atom::initMembers()
    {
        members = {
            {
                Keyword::typeString, {
                    {Keyword::Length, &Atom::resolveStringSize},
                    {Keyword::Type, &Atom::resolveType},
                }
            },
            {
                Keyword::typeArray, {
                    {Keyword::Size, &Atom::resolveArraySize},
                    {Keyword::First, &Atom::resolveArrayFirst},
                    {Keyword::Second, &Atom::resolveArraySecond},
                    {Keyword::Type, &Atom::resolveType},
                }
            },
            {
                Keyword::typeBool, {
                    {Keyword::Type, &Atom::resolveType},
                }
            },
            {
                Keyword::typeInt, {
                    {Keyword::Type, &Atom::resolveType},
                }
            },
            {
                Keyword::typeDouble, {
                    {Keyword::Type, &Atom::resolveType},
                }
            },
            {
                Keyword::typeNull, {
                    {Keyword::Type, &Atom::resolveType},
                }
            }
        };
    }

    void Atom::resolveType()
    {
        if (type == Keyword::typeInt) {
            setString(Keyword::typeInt);
        } else if (type == Keyword::typeDouble) {
            setString(Keyword::typeDouble);
        } else if (type == Keyword::typeArray) {
            setString(Keyword::typeArray);
        } else if (type == Keyword::typeString) {
            setString(Keyword::typeString);
        } else if (type == Keyword::typeBool) {
            setString(Keyword::typeBool);
        } else if (type == Keyword::typeNull) {
            setString(Keyword::Null);
        }
        setVarRef(nullptr);
        setIsCalculated();
    }

    void Atom::resolveStringSize()
    {
        setInt(stringVal.size());
        setVarRef(nullptr);
        setIsCalculated();
    }

    void Atom::resolveArraySize()
    {
        setInt(arrayVal.size());
        setVarRef(nullptr);
        setIsCalculated();
    }

    void Atom::resolveArrayFirst()
    {
        if (getVarRef() != nullptr) {
            auto varRef = getVarRef();
            if (varRef->getArray().size() < 1) {
                throw runtime_error("First element of array does not exist.");
            }
            setAtom(*(varRef->getArray().begin()->second));
            setVarRef(varRef->getArray().begin()->second);
        } else {
            if (arrayVal.size() < 1) {
                throw runtime_error("First element of array does not exist.");
            }
            setAtom(*(arrayVal.begin()->second));
            setVarRef(nullptr);
        }
    }

    void Atom::resolveArraySecond()
    {
        if (getVarRef() != nullptr) {
            auto varRef = getVarRef();
            if (varRef->getArray().size() < 2) {
                throw runtime_error("Second element of array does not exist.");
            }
            setAtom(*((++(varRef->getArray().begin()))->second));
            setVarRef((++(varRef->getArray().begin()))->second);
        } else {
            if (arrayVal.size() < 2) {
                throw runtime_error("Second element of array does not exist.");
            }
            setAtom(*((++(arrayVal.begin()))->second));
            setVarRef(nullptr);
        }
    }

    void Atom::resolveMember(wstring name)
    {
        if (!members.count(type)) {
            throw runtime_error(
                "Atom of type '" 
                + Tools::wideStrToStr(type) 
                + "' does not have members."
            );
        }

        if (!members[type].count(name)) {
            throw runtime_error(
                "Atom of type '" 
                + Tools::wideStrToStr(type) 
                + "' does not have a member '" 
                + Tools::wideStrToStr(name) 
                + "'."
            );
        }

        (this->*members[type][name])();
    }

}