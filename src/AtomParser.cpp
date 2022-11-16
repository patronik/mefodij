#include "../include/AtomParser.h"

namespace Mefodij {

    AtomParser::AtomParser() : Parser(), lastResult(nullptr), stack(), coreResolver()
    {
    }

    bool AtomParser::parseFunctionCallAtom(wstring varName, shared_ptr<Atom> & atom)
    {
        // function call left parentheses
        wchar_t symbol = readChar();
        if (symbol != L'(') {
            unreadChar();
            return false;
        }

        // resolve core function
        if (coreResolver.hasFunction(varName)) {
            resolveCoreFunctionCall(varName, atom);
            return true;
        }

        // check if function exists
        if (!getContext()->hasFunction(varName)) {
            throw runtime_error("'" + Tools::wideStrToStr(varName) + "' is not a function.");
        }

        pair<int, map<int, tuple<wstring, shared_ptr<Atom>, bool>>> & funcData = getContext()->getFunction(varName);

        shared_ptr<Context> functionStack = prepareCallStack(funcData.second);

        functionStack->setParent(getContext());

        // push function data onto stack
        stack.push_back(functionStack);

        auto prevState = getState();

        // point parser to function body
        setState({funcData.first, src, L"", false, false, nullptr});

        // execute function body
        evaluateBlockOrStatement();
        if (isReturn) {
            // atom is a result of function call
            atom->setAtom(*lastResult);
        }

        // pop function data from stack
        stack.pop_back();

        setState(prevState);

        return true;
    }

    bool AtomParser::parseCharacterConstAtom(wstring varName, shared_ptr<Atom> & atom)
    {
        if (varName == Keyword::True) {
            atom->setBool(true);
        } else if (varName == Keyword::False) {
            atom->setBool(false);
        }  else if (varName == Keyword::Null) {
            atom->setNull();
        } else {
            return false;
        }
        return true;
    }

    bool AtomParser::parseDoubleQuotedStringAtom(wchar_t symbol, shared_ptr<Atom> & atom)
    {
        // string in double quotes
        if (symbol == L'"') {
            wstring str{};
            
            while (symbol = readChar(false, true)) {
                // parse escape sequence
                if (symbol == L'\\') {
                    symbol = readChar(false, true);
                    if (symbol == L'n') {
                        str.push_back(L'\n');
                    } else if (symbol == L't') {
                        str.push_back(L'\t');
                    } else if (symbol == L'r') {
                        str.push_back(L'\r');
                    } else if (symbol == L'\\') {
                        str.push_back(L'\\');
                    } else if (symbol == L'"') {
                        str.push_back(L'"');
                    } else {
                        str.push_back(L'\\');
                        str.push_back(symbol);
                    }
                    continue;
                } else {
                    if (symbol == L'"') {
                        break;                    
                    } else {
                        str.push_back(symbol);
                    }
                }
            }
            atom->setString(str);
            return true;
        }
        return false;
    }

    bool AtomParser::parseSingleQuotedStringAtom(wchar_t symbol, shared_ptr<Atom> & atom)
    {
        // string in single quotes
        if (symbol == L'\'') {
            wstring str{};
            while (symbol = readChar(false, true)) {
                // parse escape sequence
                if (symbol == L'\\') {
                    symbol = readChar(false, true);
                    if (symbol == L'\\') {
                        str.push_back(L'\\');
                    } else if (symbol == L'\'') {
                        str.push_back(L'\'');
                    } else {
                        str.push_back(L'\\');
                        str.push_back(symbol);
                    }
                    continue;
                } else {
                    if (symbol == L'\'') {
                        break;                    
                    } else {
                        str.push_back(symbol);
                    }
                }
            }
            atom->setString(str);
            return true;
        }
        return false;
    }

    bool AtomParser::parseBinNumberLiteralAtom(shared_ptr<Atom> & atom)
    {   
        wstring number{};
        wchar_t symbol;
        while (symbol = readChar(false, true)) {
            if (binChars.find(symbol) != wstring::npos) {
                number.push_back(symbol);
                continue;
            }

            unreadChar(1, true);
            break;
        }
        atom->setInt(wcstol(number.c_str(), nullptr, 2));
        return true;
    }

    bool AtomParser::parseHexNumberLiteralAtom(shared_ptr<Atom> & atom) 
    {
        wstring number{};
        wchar_t symbol;
        while (symbol = readChar(false, true)) {
            if (hexChars.find(symbol) != wstring::npos) {
                number.push_back(symbol);
                continue;
            }

            unreadChar(1, true);
            break;
        }
        atom->setInt(wcstol(number.c_str(), nullptr, 16));
        return true;
    }

    bool AtomParser::parseNumberLiteralAtom(wchar_t symbol, shared_ptr<Atom> & atom)
    {
        wstring number{};
        if (Tools::isNumber(symbol)) {
            number.push_back(symbol);

            // Check for other bases
            symbol = readChar(false, true);
            if (number[0] == L'0' && (symbol == L'д' || symbol == L'Д')) {
                number.push_back(symbol);
                return parseBinNumberLiteralAtom(atom);
            } else if (number[0] == L'0' && (symbol == L'ш' || symbol == L'Ш')) {
                number.push_back(symbol);
                return parseHexNumberLiteralAtom(atom);
            } else {
                unreadChar(1, true);
            }

            // Decimal int or double
            bool hasDot = false;
            while (symbol = readChar(false, true)) {
                if (Tools::isNumber(symbol))  {
                    number.push_back(symbol);
                    continue;
                } else if (symbol == L'.') {
                    
                    // Check if member access
                    int posBk = pos;
                    wstring memberName{};
                    if (parseCharacterSequence(readChar(), memberName)) {
                        if (Tools::inVector<wstring>(Atom::getMemberNames(), memberName)) {
                            // member access on number
                            pos = posBk;
                            unreadChar(1, true);

                            if (hasDot) {
                                atom->setDouble(wcstod(number.c_str(), nullptr));
                            } else {
                                atom->setInt(wcstol(number.c_str(), nullptr, 10));
                            }

                            return true;
                        } else {
                            pos = posBk;
                        }

                    } else {
                        pos = posBk;
                    }

                    if (hasDot) {
                        throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
                    }
                    hasDot = true;
                    number.push_back(symbol);
                    continue;
                }

                unreadChar(1, true);
                break;
            }

            if (hasDot) {
                atom->setDouble(wcstod(number.c_str(), nullptr));
            } else {
                atom->setInt(wcstol(number.c_str(), nullptr, 10));
            }
            return true;
        }
        return false;
    }

    bool AtomParser::parseArrayLiteralAtom(wchar_t symbol, shared_ptr<Atom> & atom)
    {
        if (symbol != L'[') {
            return false;
        }

        atom->setArray(map<wstring, shared_ptr<Atom>, Tools::arrayCmp>{});

        // handle empty array
        symbol = readChar();
        if (symbol == L']') {
            return true;
        } else {
            unreadChar();
        }

        int implicitKey = 0;
        do {
            shared_ptr<Atom> keyOrVal = evaluateBoolExpression();
            symbol = readChar();
            if (symbol == L',' || symbol == L']') {

                // Implicit integer key
                keyOrVal->setKey(Tools::to_wstring(implicitKey++));
                atom->setElementAt(keyOrVal->getKey(), keyOrVal);
                
            } else if (symbol == L'=') {
                symbol = readChar();
                if (symbol == L'>') {
                    shared_ptr<Atom> arrayVal = evaluateBoolExpression();
                    if (keyOrVal->getType() == Keyword::typeString) {
                        
                        // String key
                        arrayVal->setKey(keyOrVal->getString());
                        atom->setElementAt(arrayVal->getKey(), arrayVal);

                    } else if (keyOrVal->getType() == Keyword::typeInt) {
                        if (keyOrVal->getInt() >= implicitKey) {
                            implicitKey = keyOrVal->getInt() + 1;
                        }

                        // Integer key
                        arrayVal->setKey(Tools::to_wstring(keyOrVal->getInt()));
                        atom->setElementAt(arrayVal->getKey(), arrayVal);

                    } else {
                        throw runtime_error("Only string and integer array keys are supported.");
                    }

                    symbol = readChar();
                } else {
                    throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
                }
            }
        } while (symbol == L',');

        if (symbol != L']') {
            throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
        }

        return true;
    }

    bool AtomParser::parseAlphabeticalAtom(wchar_t symbol, shared_ptr<Atom> & atom)
    {
        // alphabetical atom
        wstring varName{};
        if (parseCharacterSequence(symbol, varName)) {
            // try to recognize keyword 
            if (parseCharacterConstAtom(varName, atom)) {
                return true;
            }

            // check if sequence is reserved 
            if (Tools::inVector<wstring>(reservedKeywords, varName)) {
                throw runtime_error("This name '" + Tools::wideStrToStr(varName) + "' is reserved.");
            }

            // try to process function call atom
            if (parseFunctionCallAtom(varName, atom)) {
                return true;
            }

            // variable atom
            shared_ptr<Context> storage = getContext();
            if (!storage->hasVar(varName)) {
                throw runtime_error("Variable '" + Tools::wideStrToStr(varName) + "' is not defined.");
            }

            // copy variable state to atom 
            atom->setAtom(*storage->getVar(varName));
            // store reference to variable into atom
            atom->setVarRef(storage->getVar(varName));
            return true;
        }
        return false;
    }

    bool AtomParser::parseParentheticalAtom(wchar_t symbol, shared_ptr<Atom> & atom)
    {
        if (symbol == L'(') {

            // Check for type casting
            int posBk = pos;
            wstring cast;
            if (parseCharacterSequence(readChar(), cast)) {
                if (Tools::inVector<wstring>(Keyword::getTypes(), cast)) {
                    if (readChar() == L')') {
                        // Type casting
                        atom = parseAtom();
                        atom->cast(cast);
                        return true;
                    } else {
                        pos = posBk;
                    }
                } else {
                    pos = posBk;
                }
            } else {
                pos = posBk;
            }

            shared_ptr<Atom> subExpr = evaluateBoolStatement();

            if (readChar() != L')') {
                throw runtime_error("Syntax error. Wrong number of parentheses.");
            }

            // atom is a result of subexpression
            atom = subExpr;

            return true;
        }
        return false;
    }

    shared_ptr<Atom> AtomParser::parseAtom()
    {
        bool isReference = false;
        bool boolInversion = false;
        wstring preOperator{};

        wchar_t atomChar = readChar();

        // check for reference "&"
        if (atomChar == L'&') {
            isReference = true;
            atomChar = readChar();
        }

        // check for boolean inversion
        if (atomChar == L'!') {
            boolInversion = true;
            atomChar = readChar();
        }

        // unary plus and pre increment
        if (atomChar == L'+') {
            preOperator += atomChar;
            atomChar = readChar();
            // check for pre increment
            if (atomChar == L'+') {
                preOperator += atomChar;
                atomChar = readChar();
            }
        }

        // unary minus and pre decrement
        if (atomChar == L'-') {
            preOperator += atomChar;
            atomChar = readChar();
            // check for pre decrement
            if (atomChar == L'-') {
                preOperator += atomChar;
                atomChar = readChar();
            }
        }

        // statement atom
        shared_ptr<Atom> atom = make_shared<Atom>(nullptr);

        parseParentheticalAtom(atomChar, atom)
        || parseAlphabeticalAtom(atomChar, atom)
        || parseArrayLiteralAtom(atomChar, atom)
        || parseNumberLiteralAtom(atomChar, atom)
        || parseSingleQuotedStringAtom(atomChar, atom)
        || parseDoubleQuotedStringAtom(atomChar, atom);

        resolveAtomAccess(atom);
        resolveAtomAssignment(atom);

        if (preOperator.size()) {
            atom->preOperator(preOperator);
        }

        if (boolInversion) {
            atom->preOperator(L"!");
        }

        if (isReference) {
            atom->setIsReference();
        }

        return atom;
    }

}