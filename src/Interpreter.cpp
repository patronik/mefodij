#include "../include/Interpreter.h"
#include "../include/tools.h"

unique_ptr<BoolBoolJoiner> Interpreter::boolBoolJoiner = make_unique<BoolBoolJoiner>();
unique_ptr<BoolIntJoiner> Interpreter::boolIntJoiner = make_unique<BoolIntJoiner>();
unique_ptr<BoolNullJoiner> Interpreter::boolNullJoiner = make_unique<BoolNullJoiner>();
unique_ptr<BoolArrayJoiner> Interpreter::boolArrayJoiner = make_unique<BoolArrayJoiner>();
unique_ptr<BoolDoubleJoiner> Interpreter::boolDoubleJoiner = make_unique<BoolDoubleJoiner>();
unique_ptr<BoolStringJoiner> Interpreter::boolStringJoiner = make_unique<BoolStringJoiner>();
unique_ptr<IntBoolJoiner> Interpreter::intBoolJoiner = make_unique<IntBoolJoiner>();
unique_ptr<IntIntJoiner> Interpreter::intIntJoiner = make_unique<IntIntJoiner>();
unique_ptr<IntNullJoiner> Interpreter::intNullJoiner = make_unique<IntNullJoiner>();
unique_ptr<IntArrayJoiner> Interpreter::intArrayJoiner = make_unique<IntArrayJoiner>();
unique_ptr<IntDoubleJoiner> Interpreter::intDoubleJoiner = make_unique<IntDoubleJoiner>();
unique_ptr<IntStringJoiner> Interpreter::intStringJoiner = make_unique<IntStringJoiner>();
unique_ptr<NullBoolJoiner> Interpreter::nullBoolJoiner = make_unique<NullBoolJoiner>();
unique_ptr<NullIntJoiner> Interpreter::nullIntJoiner = make_unique<NullIntJoiner>();
unique_ptr<NullNullJoiner> Interpreter::nullNullJoiner = make_unique<NullNullJoiner>();
unique_ptr<NullArrayJoiner> Interpreter::nullArrayJoiner = make_unique<NullArrayJoiner>();
unique_ptr<NullDoubleJoiner> Interpreter::nullDoubleJoiner = make_unique<NullDoubleJoiner>();
unique_ptr<NullStringJoiner> Interpreter::nullStringJoiner = make_unique<NullStringJoiner>();
unique_ptr<ArrayBoolJoiner> Interpreter::arrayBoolJoiner = make_unique<ArrayBoolJoiner>();
unique_ptr<ArrayIntJoiner> Interpreter::arrayIntJoiner = make_unique<ArrayIntJoiner>();
unique_ptr<ArrayNullJoiner> Interpreter::arrayNullJoiner = make_unique<ArrayNullJoiner>();
unique_ptr<ArrayArrayJoiner> Interpreter::arrayArrayJoiner = make_unique<ArrayArrayJoiner>();
unique_ptr<ArrayDoubleJoiner> Interpreter::arrayDoubleJoiner = make_unique<ArrayDoubleJoiner>();
unique_ptr<ArrayStringJoiner> Interpreter::arrayStringJoiner = make_unique<ArrayStringJoiner>();
unique_ptr<DoubleBoolJoiner> Interpreter::doubleBoolJoiner = make_unique<DoubleBoolJoiner>();
unique_ptr<DoubleIntJoiner> Interpreter::doubleIntJoiner = make_unique<DoubleIntJoiner>();
unique_ptr<DoubleNullJoiner> Interpreter::doubleNullJoiner = make_unique<DoubleNullJoiner>();
unique_ptr<DoubleArrayJoiner> Interpreter::doubleArrayJoiner = make_unique<DoubleArrayJoiner>();
unique_ptr<DoubleDoubleJoiner> Interpreter::doubleDoubleJoiner = make_unique<DoubleDoubleJoiner>();
unique_ptr<DoubleStringJoiner> Interpreter::doubleStringJoiner = make_unique<DoubleStringJoiner>();
unique_ptr<StringBoolJoiner> Interpreter::stringBoolJoiner = make_unique<StringBoolJoiner>();
unique_ptr<StringIntJoiner> Interpreter::stringIntJoiner = make_unique<StringIntJoiner>();
unique_ptr<StringNullJoiner> Interpreter::stringNullJoiner = make_unique<StringNullJoiner>();
unique_ptr<StringArrayJoiner> Interpreter::stringArrayJoiner = make_unique<StringArrayJoiner>();
unique_ptr<StringDoubleJoiner> Interpreter::stringDoubleJoiner = make_unique<StringDoubleJoiner>();
unique_ptr<StringStringJoiner> Interpreter::stringStringJoiner = make_unique<StringStringJoiner>();

void Interpreter::joinAtoms(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{
    if (left->getType() == L"int" && right->getType() == L"int") {
        Interpreter::intIntJoiner->join(left, op, right);
    } else if (left->getType() == L"int" && right->getType() == L"double") {
        Interpreter::intDoubleJoiner->join(left, op, right);
    } else if (left->getType() == L"int" && right->getType() == L"string") {
        Interpreter::intStringJoiner->join(left, op, right);
    } else if (left->getType() == L"int" && right->getType() == L"array") {
        Interpreter::intArrayJoiner->join(left, op, right);
    } else if (left->getType() == L"int" && right->getType() == L"bool") {
        Interpreter::intBoolJoiner->join(left, op, right);
    } else if (left->getType() == L"int" && right->getType() == L"null") {
        Interpreter::intNullJoiner->join(left, op, right);
    } else if (left->getType() == L"double" && right->getType() == L"int") {
        Interpreter::doubleIntJoiner->join(left, op, right);
    } else if (left->getType() == L"double" && right->getType() == L"double") {
        Interpreter::doubleDoubleJoiner->join(left, op, right);
    } else if (left->getType() == L"double" && right->getType() == L"string") {
        Interpreter::doubleStringJoiner->join(left, op, right);
    } else if (left->getType() == L"double" && right->getType() == L"array") {
        Interpreter::doubleArrayJoiner->join(left, op, right);
    } else if (left->getType() == L"double" && right->getType() == L"bool") {
        Interpreter::doubleBoolJoiner->join(left, op, right);
    } else if (left->getType() == L"double" && right->getType() == L"null") {
        Interpreter::doubleNullJoiner->join(left, op, right);
    } else if (left->getType() == L"string" && right->getType() == L"int") {
        Interpreter::stringIntJoiner->join(left, op, right);
    } else if (left->getType() == L"string" && right->getType() == L"double") {
        Interpreter::stringDoubleJoiner->join(left, op, right);
    } else if (left->getType() == L"string" && right->getType() == L"string") {
        Interpreter::stringStringJoiner->join(left, op, right);
    } else if (left->getType() == L"string" && right->getType() == L"array") {
        Interpreter::stringArrayJoiner->join(left, op, right);
    } else if (left->getType() == L"string" && right->getType() == L"bool") {
        Interpreter::stringBoolJoiner->join(left, op, right);
    } else if (left->getType() == L"string" && right->getType() == L"null") {
        Interpreter::stringNullJoiner->join(left, op, right);
    } else if (left->getType() == L"array" && right->getType() == L"int") {
        Interpreter::arrayIntJoiner->join(left, op, right);
    } else if (left->getType() == L"array" && right->getType() == L"double") {
        Interpreter::arrayDoubleJoiner->join(left, op, right);
    } else if (left->getType() == L"array" && right->getType() == L"string") {
        Interpreter::arrayStringJoiner->join(left, op, right);
    } else if (left->getType() == L"array" && right->getType() == L"array") {
        Interpreter::arrayArrayJoiner->join(left, op, right);
    } else if (left->getType() == L"array" && right->getType() == L"bool") {
        Interpreter::arrayBoolJoiner->join(left, op, right);
    } else if (left->getType() == L"array" && right->getType() == L"null") {
        Interpreter::arrayNullJoiner->join(left, op, right);
    } else if (left->getType() == L"bool" && right->getType() == L"int") {
        Interpreter::boolIntJoiner->join(left, op, right);
    } else if (left->getType() == L"bool" && right->getType() == L"double") {
        Interpreter::boolDoubleJoiner->join(left, op, right);
    } else if (left->getType() == L"bool" && right->getType() == L"string") {
        Interpreter::boolStringJoiner->join(left, op, right);
    } else if (left->getType() == L"bool" && right->getType() == L"array") {
        Interpreter::boolArrayJoiner->join(left, op, right);
    } else if (left->getType() == L"bool" && right->getType() == L"bool") {
        Interpreter::boolBoolJoiner->join(left, op, right);
    } else if (left->getType() == L"bool" && right->getType() == L"null") {
        Interpreter::boolNullJoiner->join(left, op, right);
    } else if (left->getType() == L"null" && right->getType() == L"int") {
        Interpreter::nullIntJoiner->join(left, op, right);
    } else if (left->getType() == L"null" && right->getType() == L"double") {
        Interpreter::nullDoubleJoiner->join(left, op, right);
    } else if (left->getType() == L"null" && right->getType() == L"string") {
        Interpreter::nullStringJoiner->join(left, op, right);
    } else if (left->getType() == L"null" && right->getType() == L"array") {
        Interpreter::nullArrayJoiner->join(left, op, right);
    } else if (left->getType() == L"null" && right->getType() == L"bool") {
        Interpreter::nullBoolJoiner->join(left, op, right);
    } else if (left->getType() == L"null" && right->getType() == L"null") {
        Interpreter::nullNullJoiner->join(left, op, right);
    } else {
        pair<int, int> currLoc = getCurrentLocation();
        throw runtime_error(
            "Joiner for type " + wideStrToStr(left->getType())
            + " operator " + wideStrToStr(op)
            + " and type " + wideStrToStr(right->getType())
            + " does not exist. At " + to_string(currLoc.first) 
            + ":" 
            + to_string(currLoc.second) 
            + "."
        );
    }
}

Interpreter::Interpreter() : Parser()
{
}

Interpreter::Variables & Interpreter::getStorageRef()
{
    if (stack.size() > 0) {
        return stack.at(stack.size() - 1);
    }
    return variables;
}

bool Interpreter::parseDoubleQuotedStringAtom(wchar_t symbol, const shared_ptr<Atom> atom)
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

bool Interpreter::parseSingleQuotedStringAtom(wchar_t symbol, const shared_ptr<Atom> atom)
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

bool Interpreter::parseKeywordAtom(wstring varName, const shared_ptr<Atom> atom)
{
    if (inVector<wstring>(Atom::castTypes, varName)) {
            atom->setCast(varName);
        } else if (varName == L"true") {
            atom->setBool(true);
        } else if (varName == L"false") {
            atom->setBool(false);
        }  else if (varName == L"null") {
            atom->setNull();
        } else {
            return false;
        }
        return true;
}

bool Interpreter::parseFunctionCallAtom(wstring varName, const shared_ptr<Atom> atom)
{
    // check if function exists
    if (!functions.has(varName)) {
        return false;
    }

    // function call left parentheses
    wchar_t symbol = readChar();
    if (symbol != L'(') {
        unreadChar();
        return false;
    }

    pair<int, map<int, pair<wstring, shared_ptr<Atom>>>> & funcData = functions.get(varName);
    Interpreter::Variables functionStack;
    symbol = readChar();
    if (symbol != L')') {
        unreadChar();
        // parse arguments
        int argumentIndex = 0;
        do {
            if (funcData.second.count(argumentIndex)) {
                functionStack.set(funcData.second.at(argumentIndex).first, evaluateBoolStatement());
            } else {
                // skip arguments which are not expected by function
                fastForward({L','});
                unreadChar();
            }
            argumentIndex++;
            symbol = readChar();
        } while (symbol == L',');


        // Check required paramaters and set parameters with default values
        while(funcData.second.count(argumentIndex)) {
            // No intializer means required parameter is missing
            if (funcData.second.at(argumentIndex).second == nullptr) {
                pair<int, int> currLoc = getCurrentLocation();
                throw runtime_error("Function required parameter "
                    + wideStrToStr(funcData.second.at(argumentIndex).first)
                    + " is missing. At " 
                    + to_string(currLoc.first) 
                    + ":" 
                    + to_string(currLoc.second) 
                    + "."
                );
            } else {
                // Set default value
                functionStack.set(
                    funcData.second.at(argumentIndex).first, 
                    funcData.second.at(argumentIndex).second
                );
            }
            argumentIndex++;
        }
    }

    if (symbol != L')') {
        pair<int, int> currLoc = getCurrentLocation();
        throw runtime_error("Unexpected token '" 
            + wideStrToStr(symbol) 
            + "'. At " 
            + to_string(currLoc.first) 
            + ":" 
            + to_string(currLoc.second) 
            + "."
        );
    }

    // push function data onto stack
    stack.push_back(functionStack);

    // backup state
    tuple<int, bool, shared_ptr<Atom>, wstring> prevState{pos, isReturn, lastResult, dynamicSrc};

    // point parser to function body
    dynamicSrc = L"";
    pos = funcData.first;
    isReturn = false;

    // execute function body
    evaluateBlockOrStatement();
    if (isReturn) {
        // assign function result as atom
        *atom = *lastResult;
    }

    // pop function data from stack
    stack.pop_back();

    // restore state
    dynamicSrc = get<3>(prevState);
    lastResult = get<2>(prevState);
    isReturn = get<1>(prevState);
    pos = get<0>(prevState);

    return true;
}

bool Interpreter::parseNumberLiteralAtom(wchar_t symbol, const shared_ptr<Atom> atom)
{
    wstring number{};
    bool hasDot = false;
    if (isNumber(symbol)) {
        number.push_back(symbol);
        while (symbol = readChar(false, true)) {
            if (isNumber(symbol))  {
                number.push_back(symbol);
                continue;
            } else if (symbol == L'.') {
                if (hasDot) {
                    pair<int, int> currLoc = getCurrentLocation();
                    throw runtime_error("Unexpected token '" 
                        + wideStrToStr(symbol) 
                        + "'. At " 
                        + to_string(currLoc.first) 
                        + ":" 
                        + to_string(currLoc.second) 
                        + "."
                    );
                }
                hasDot = true;
                number.push_back(symbol);
                continue;
            }

            if (!isSpace(symbol)) {
                unreadChar();
            }
            break;
        }

        if (symbol == L'.') {
            pair<int, int> currLoc = getCurrentLocation();
            throw runtime_error("Unexpected token '" 
                + wideStrToStr(symbol) 
                + "'."
            );
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

bool Interpreter::parseArrayAccessAtom(wstring varName, const shared_ptr<Atom> atom)
{
    // array element
    wchar_t symbol = readChar();
    if (symbol != L'[') {
        unreadChar();
        return false;
    }

    vector<shared_ptr<Atom>> elementKeys{};
    do {
        shared_ptr<Atom> keyAtom = evaluateBoolExpression();
        if (!inVector<wstring>({L"string", L"int", L"double"}, keyAtom->getType())) {
            pair<int, int> currLoc = getCurrentLocation();
            throw runtime_error("Only string and integer array keys are supported. At " 
                + to_string(currLoc.first) 
                + ":" 
                + to_string(currLoc.second) 
                + "."
            );
        }
        elementKeys.push_back(keyAtom);

        symbol = readChar();
        if (symbol == L'\0') {
            pair<int, int> currLoc = getCurrentLocation();
            throw runtime_error("Unexpected end of file. At " 
                + to_string(currLoc.first) 
                + ":" 
                + to_string(currLoc.second) 
                + "."
            );
        }
        if (symbol != L']') {
            pair<int, int> currLoc = getCurrentLocation();
            throw runtime_error("Unexpected token '" 
                + wideStrToStr(symbol) 
                + "'. At " 
                + to_string(currLoc.first) 
                + ":" 
                + to_string(currLoc.second) 
                + "."
            );
        }
        symbol = readChar();
    } while (symbol == L'[');

    unreadChar();

    Interpreter::Variables storage = getStorageRef();
    // initialize to empty array if not exists
    if (!storage.has(varName)) {
        storage.set(varName,  make_shared<Atom>(map<wstring, shared_ptr<Atom>>{}));
    }

    shared_ptr<Atom> target = storage.get(varName);

    for (int key = 0; key < elementKeys.size(); key++) {
        if (key < (elementKeys.size() - 1)) {
            if (!target->issetAt(elementKeys[key]->toString())) {
                target->createAt(
                    elementKeys[key]->toString(),
                    make_shared<Atom>(map<wstring, shared_ptr<Atom>>{})
                );
            }
        }
        target = target->elementAt(elementKeys[key]->toString());
    }

    *atom = *target;
    atom->setVar(target);
    return true;
}

bool Interpreter::parseArrayLiteralAtom(wchar_t symbol, const shared_ptr<Atom> atom)
{
    if (symbol != L'[') {
        return false;
    }

    map<wstring, shared_ptr<Atom>> array{};
    int implicitKey = 0;
    do {
        shared_ptr<Atom> keyOrVal = evaluateBoolExpression();
        symbol = readChar();
        if (symbol == L',' || symbol == L']') {
            array[to_wstring(implicitKey++)] = keyOrVal;
        } else if (symbol == L'=') {
            symbol = readChar();
            if (symbol == L'>') {
                shared_ptr<Atom> arrayVal = evaluateBoolExpression();
                if (keyOrVal->getType() == L"string") {
                    array[keyOrVal->getString()] = arrayVal;
                } else if (keyOrVal->getType() == L"int") {
                    if (keyOrVal->getInt() >= implicitKey) {
                        implicitKey = keyOrVal->getInt() + 1;
                    }
                    array[to_wstring(keyOrVal->getInt())] = arrayVal;
                } else if (keyOrVal->getType() == L"double") {
                    array[to_wstring(keyOrVal->getDouble())] = arrayVal;
                } else {
                    pair<int, int> currLoc = getCurrentLocation();
                    throw runtime_error("Only string and numeric array keys are supported. At " 
                        + to_string(currLoc.first) 
                        + ":" 
                        + to_string(currLoc.second) 
                        + "."
                    );
                }

                symbol = readChar();
            } else {
                pair<int, int> currLoc = getCurrentLocation();
                throw runtime_error("Unexpected token '" 
                    + wideStrToStr(symbol) 
                    + "'. At " 
                    + to_string(currLoc.first) 
                    + ":" 
                    + to_string(currLoc.second) 
                    + "."
                );
            }
        }
    } while (symbol == L',');

    if (symbol != L']') {
        pair<int, int> currLoc = getCurrentLocation();
        throw runtime_error("Unexpected token '" 
            + wideStrToStr(symbol) 
            + "'. At " 
            + to_string(currLoc.first) 
            + ":" 
            + to_string(currLoc.second) 
            + "."
        );
    }

    atom->setArray(array);

    return true;
}

bool Interpreter::parseAlphabeticalAtom(wchar_t symbol, const shared_ptr<Atom> atom)
{
    // alphabetical atom
    wstring varName{};
    if (parseCharacterSequence(symbol, varName)) {
        // try to parse keyword atom
        if (parseKeywordAtom(varName, atom)) {
            return true;
        }

        // try to process function call atom
        if (parseFunctionCallAtom(varName, atom)) {
            return true;
        }

        // try to parse array element
        if (parseArrayAccessAtom(varName, atom)) {
            return true;
        }

        // variable atom
        Interpreter::Variables & storage = getStorageRef();
        if (!storage.has(varName)) {
            storage.set(varName, make_shared<Atom>());
        }

        // copy variable value to atom
        *atom = *storage.get(varName);
        atom->setVar(storage.get(varName));
        return true;
    }
    return false;
}

shared_ptr<Atom> Interpreter::parseAtom()
{
    bool boolInversion = false;
    wstring preOperator{};

    wchar_t atomChar = readChar();

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

    shared_ptr<Atom> atom = make_shared<Atom>();

    evaluateParentheticalAtom(atomChar, atom)
    || parseAlphabeticalAtom(atomChar, atom)
    || parseArrayLiteralAtom(atomChar, atom)
    || parseNumberLiteralAtom(atomChar, atom)
    || parseSingleQuotedStringAtom(atomChar, atom)
    || parseDoubleQuotedStringAtom(atomChar, atom);

    if (preOperator.size()) {
        atom->preOperator(preOperator);
    }

    if (boolInversion) {
        atom->preOperator(L"!");
    }

    return atom;
}

shared_ptr<Atom> Interpreter::evaluateMathBlock()
{
    shared_ptr<Atom> result = parseAtom();
    wchar_t symbol;
    wchar_t atomOp;
    while (atomOp = readChar(true)) {
        switch (atomOp) {
            case L'*':
                joinAtoms(result, L"*", parseAtom());
            break;
            case L'/':
                joinAtoms(result, L"/", parseAtom());
            break;
            case L'.':
                joinAtoms(result, L".", parseAtom());
            break;
            case L'%':
                joinAtoms(result, L"%", parseAtom());
            break;
            case L'+':
                symbol = readChar();
                if (symbol == L'+') {
                    result->postOperator(L"++");
                } else if (symbol == L'=') {
                    joinAtoms(result, L"+", evaluateBoolStatement());
                    joinAtoms(result, L"=", result);
                } else {
                    // Lower lever operator
                    unreadChar(2);
                    return result;
                }
            break;
            case L'-':
                symbol = readChar();
                if (symbol == L'-') {
                    result->postOperator(L"--");
                } else if (symbol == L'=') {
                    joinAtoms(result, L"-", evaluateBoolStatement());
                    joinAtoms(result, L"=", result);
                } else {
                    // Lower lever operator
                    unreadChar(2);
                    return result;
                }
                break;
            case L'=':
                symbol = readChar();
                if (symbol == L'=') {
                    // equality
                    unreadChar(2);
                    return result;
                    break;
                } else if (symbol == L'>')  {
                    // key-val separator
                    unreadChar(2);
                    return result;
                    break;
                } else {
                    unreadChar();
                    // execute assignment statement
                    joinAtoms(result, L"=", evaluateBoolStatement());
                }
                break;
            // Lower lever operators
            case L'!': // boolean not
            case L'>': // less than
            case L'<': // greater than
            case L'&': // boolean "and" &&
            case L'|': // boolean "or" ||
            case L'м': // check against regex
            case L'i': // find in set
            // end of argument or statement
            case L',':
            // end of subexpression
            case L')':
            // end of statement
            case L';':
            // array value parsed
            case L']':
                // start of statement block
                unreadChar();
                return result;
                break;
            default:
                pair<int, int> currLoc = getCurrentLocation();
                throw runtime_error("Unexpected token '" 
                    + wideStrToStr(atomOp) 
                    + "'. At " 
                    + to_string(currLoc.first) 
                    + ":" 
                    + to_string(currLoc.second) 
                    + "."
                );
                break;
        }
    }
    return result;
}

shared_ptr<Atom> Interpreter::evaluateBoolExpression()
{
    shared_ptr<Atom> result = evaluateMathBlock();
    wchar_t mathOp;
    wchar_t symbol;
    while (mathOp = readChar(true)) {
        switch (mathOp) {
            case L'+':
                joinAtoms(result, L"+", evaluateMathBlock());
            break;
            case L'-':
                joinAtoms(result, L"-", evaluateMathBlock());
            break;
            case L'=':
                symbol = readChar();
                if (symbol == L'=') {
                    joinAtoms(result, L"==", evaluateMathBlock());
                } else if (symbol == L'>')  {
                    // key-val separator
                    unreadChar(2);
                    return result;
                    break;
                } else {
                    pair<int, int> currLoc = getCurrentLocation();
                    throw runtime_error("Unexpected token '"
                        + wideStrToStr(mathOp)
                        + wideStrToStr(symbol)
                        + "'. At " 
                        + to_string(currLoc.first) 
                        + ":" 
                        + to_string(currLoc.second) 
                        + "."
                    );
                }
            break;
            case L'!':
                symbol = readChar();
                if (symbol == L'=') {
                    joinAtoms(result, L"!=", evaluateMathBlock());
                } else {
                    pair<int, int> currLoc = getCurrentLocation();
                    throw runtime_error("Unexpected token '"
                        + wideStrToStr(mathOp)
                        + wideStrToStr(symbol)
                        + "'. At " 
                        + to_string(currLoc.first) 
                        + ":" 
                        + to_string(currLoc.second) 
                        + "."
                    );
                }
            break;
            case L'>':
                symbol = readChar();
                if (symbol == L'=') {
                    joinAtoms(result, L">=", evaluateMathBlock());
                } else {
                    unreadChar();
                    joinAtoms(result, L">", evaluateMathBlock());
                }
            break;
            case L'<':
                symbol = readChar();
                if (symbol == L'=') {
                    joinAtoms(result, L"<=", evaluateMathBlock());
                } else {
                    unreadChar();
                    joinAtoms(result, L"<", evaluateMathBlock());
                }
                break;
            case L'i': // find in set
                symbol = readChar(true);
                if (symbol == L'n') {
                    joinAtoms(result, L"in", evaluateMathBlock());
                } else {
                    pair<int, int> currLoc = getCurrentLocation();
                    throw runtime_error("Unexpected token '"
                        + wideStrToStr(mathOp)
                        + wideStrToStr(symbol)
                        + "'. At " 
                        + to_string(currLoc.first) 
                        + ":" 
                        + to_string(currLoc.second) 
                        + "."
                    );
                }
            break;
            case L'м': // check against regex
                for (auto tmp: vector<wchar_t>{L'а', L'т', L'ч'}) {
                    symbol = readChar(true);
                    if (symbol != tmp) {
                        pair<int, int> currLoc = getCurrentLocation();
                        throw runtime_error("Unexpected token '" 
                            + wideStrToStr(symbol) 
                            + "'. At " 
                            + to_string(currLoc.first) 
                            + ":" 
                            + to_string(currLoc.second) 
                            + "."
                        );
                    }
                }
                joinAtoms(result, L"матч", evaluateBoolExpression());
            break;
            // Lower lever operators
            case L'&': // boolean "and" &&
            case L'|': // boolean "or" ||
            // end of argument or statement
            case L',':
            // end of subexpression
            case L')':
            // end of statement
            case L';':
            // array value parsed
            case L']':
                unreadChar();
                // return result from recursive call
                return result;
                break;
            default:
                pair<int, int> currLoc = getCurrentLocation();
                throw runtime_error("Unexpected token '" 
                    + wideStrToStr(mathOp) 
                    + "'. At " 
                    + to_string(currLoc.first) 
                    + ":" 
                    + to_string(currLoc.second) 
                    + "."
                );
                break;
        }
    }
    return result;
}

shared_ptr<Atom> Interpreter::evaluateBoolStatement()
{
    /**
     * If expression contains only 1 math block - return as math expression result,
     * otherwise cast type of result to boolean
     */
    shared_ptr<Atom> result = evaluateBoolExpression();
    wchar_t booleanOp;
    wchar_t symbol;
    while (booleanOp = readChar(true)) {
        switch (booleanOp) {
            case L'|':
                symbol = readChar();
                if (symbol == L'|') {
                    if (result->toBool()) {
                        // in order to reduce amount of calculations,
                        // skip the rest of expression and return result
                        fastForward({L';', L')'}, L'(');
                        unreadChar();
                        return result;
                    }
                    joinAtoms(result, L"||", evaluateBoolExpression());
                } else {
                    pair<int, int> currLoc = getCurrentLocation();
                    throw runtime_error("Unexpected token '"
                        + wideStrToStr(booleanOp)
                        + wideStrToStr(symbol)
                        + "'. At " 
                        + to_string(currLoc.first) 
                        + ":" 
                        + to_string(currLoc.second) 
                        + "."
                    );
                }
                break;
            case L'&':
                symbol = readChar();
                if (symbol == L'&') {
                    if (!result->toBool()) {
                        // in order to reduce amount of calculations,
                        // skip the rest of expression and return result
                        fastForward({L';', L')'}, L'(');
                        unreadChar();
                        return result;
                    }
                    joinAtoms(result, L"&&", evaluateBoolExpression());
                } else {
                    pair<int, int> currLoc = getCurrentLocation();
                    throw runtime_error("Unexpected token '"
                        + wideStrToStr(booleanOp)
                        + wideStrToStr(symbol)
                        + "'. At " 
                        + to_string(currLoc.first) 
                        + ":" 
                        + to_string(currLoc.second) 
                        + "."
                    );
                }
                break;
            // end of argument
            case L',':
            // end of subexpression
            case L')':
            // end of statement
            case L';':
                unreadChar();
                // return result from recursive call
                return result;
                break;
            default:
                pair<int, int> currLoc = getCurrentLocation();
                throw runtime_error("Unexpected token '" 
                    + wideStrToStr(booleanOp) 
                    + "'. At " 
                    + to_string(currLoc.first) 
                    + ":" 
                    + to_string(currLoc.second) 
                    + "."
                );
                break;
        }
    }
    return result;
}

bool Interpreter::evaluateParentheticalAtom(wchar_t symbol, const shared_ptr<Atom> atom)
{
    if (symbol == L'(') {
        shared_ptr<Atom> subResult = evaluateBoolStatement();
        if (readChar() != L')') {
            pair<int, int> currLoc = getCurrentLocation();
            throw runtime_error("Syntax error. Wrong number of parentheses. At " 
                + to_string(currLoc.first) 
                + ":" 
                + to_string(currLoc.second) 
                + "."
            );
        }
        if (subResult->getType() == Atom::typeCast) {
            // Type casting
            *atom = *parseAtom();
            atom->cast(subResult->getCast());
        } else {
            // Subexpression
            *atom = *subResult;
        }
        return true;
    }
    return false;
}

void Interpreter::evaluateForLoop()
{
    wchar_t symbol;
    if ((symbol = readChar()) != L'(') {
        pair<int, int> currLoc = getCurrentLocation();
        throw runtime_error("Unexpected token '" 
            + wideStrToStr(symbol) 
            + "'. At " 
            + to_string(currLoc.first) 
            + ":" 
            + to_string(currLoc.second) 
            + "."
        );
    }

    // Initializer statement
    evaluateStatement();

    if ((symbol = readChar()) != L';') {
        pair<int, int> currLoc = getCurrentLocation();
        throw runtime_error("Unexpected token '" 
            + wideStrToStr(symbol) 
            + "'. At " 
            + to_string(currLoc.first) 
            + ":" 
            + to_string(currLoc.second) 
            + "."
        );
    }

    int conditionPos = pos;
    int postStatementPos = -1;
    int loopBodyPos = -1;

    do {
        evaluateStatement();
        if ((symbol = readChar()) != L';') {
            pair<int, int> currLoc = getCurrentLocation();
            throw runtime_error("Unexpected token '" 
                + wideStrToStr(symbol) 
                + "'. At " 
                + to_string(currLoc.first) 
                + ":" 
                + to_string(currLoc.second) 
                + 
                "."
            );
        }

        if (!lastResult->toBool()) {
            break;
        }

        if (postStatementPos == -1) {
            postStatementPos = pos;
        }

        if (loopBodyPos == -1) {
            fastForward({L')'}, L'(');
            loopBodyPos = pos;
        } else {
            pos = loopBodyPos;
        }

        evaluateBlockOrStatement(true);
        if (isBreak || isReturn) {
            break;
        }

        // Evaluate after statement
        pos = postStatementPos;
        evaluateStatement();

        // Prepare for next iteration
        pos = conditionPos;

    } while(true);

    pos = conditionPos;
    fastForward({L')'}, L'(');
    skipBlockOrStatement();

    isBreak = false;
}

void Interpreter::evaluateBlockOrStatement(bool stopOnBreak)
{
    wchar_t symbol;
    if ((symbol = readChar()) != L'{') {
        // evaluate 1 statement
        unreadChar();
        evaluateStatement();
        if ((symbol = readChar()) != L';') {
            pair<int, int> currLoc = getCurrentLocation();
            throw runtime_error("Unexpected token '" 
                + wideStrToStr(symbol) 
                + "'. At " 
                + to_string(currLoc.first) 
                + ":" 
                + to_string(currLoc.second) 
                + "."
            );
        }
    } else {
        wchar_t statementOp;
        int depth = 0;
        // evaluate 1 code block
        evaluateStatement();
        while (!isReturn && (!stopOnBreak || !isBreak) && (statementOp = readChar())) {
            switch (statementOp) {
                case L'{':
                    depth++;
                break;
                case L'}':
                    if (depth == 0) {
                        return;
                    }
                    depth--;
                break;
                // end of statement
                case L';':
                    evaluateStatement();
                    break;
                default:
                    pair<int, int> currLoc = getCurrentLocation();
                    throw runtime_error("Unexpected token '" 
                        + wideStrToStr(statementOp) 
                        + "'.  At " 
                        + to_string(currLoc.first) 
                        + ":" 
                        + to_string(currLoc.second) 
                        + "."
                    );
                break;
            }
        }
    }
}

void Interpreter::evaluateIfStructure()
{
    shared_ptr<Atom> lastIfResult = make_shared<Atom>();
    wchar_t symbol;
    if ((symbol = readChar()) != L'(') {
        pair<int, int> currLoc = getCurrentLocation();
        throw runtime_error("Unexpected token '" 
            + wideStrToStr(symbol) 
            + "'. At " 
            + to_string(currLoc.first) 
            + ":" 
            + to_string(currLoc.second) 
            + "."
        );
    }

    evaluateParentheticalAtom(symbol, lastIfResult);

    if (lastIfResult->toBool()) {
        evaluateBlockOrStatement();
        if (isReturn) {
            return;
        }
    } else {
        skipBlockOrStatement();
    }

    bool elseFound = false;
    while (!isReturn) {
        if ((symbol = readChar(true)) != L'а') {
            if (symbol != endOfFile) {
                unreadChar();
            }
            break;
        }

        for (auto tmp: vector<wchar_t>{L'б', L'о'}) {
            symbol = readChar(true);
            if (symbol != tmp) {
                pair<int, int> currLoc = getCurrentLocation();
                throw runtime_error("Unexpected token '" 
                    + wideStrToStr(symbol) 
                    + "'. At " 
                    + to_string(currLoc.first) 
                    + ":" 
                    + to_string(currLoc.second) 
                    + "."
                );
            }
        }

        if ((symbol = readChar(true)) == L'я') {
            for (auto tmp: vector<wchar_t>{L'к', L'щ', L'о'}) {
                symbol = readChar(true);
                if (symbol != tmp) {
                    pair<int, int> currLoc = getCurrentLocation();
                    throw runtime_error("Unexpected token '" 
                        + wideStrToStr(symbol) 
                        + "'. At " 
                        + to_string(currLoc.first) 
                        + ":" 
                        + to_string(currLoc.second) 
                        + "."
                    );
                }
            }

            if (lastIfResult->toBool()) {
                if ((symbol = readChar()) != L'(') {
                    pair<int, int> currLoc = getCurrentLocation();
                    throw runtime_error("Unexpected token '" 
                        + wideStrToStr(symbol) 
                        + "'. At " 
                        + to_string(currLoc.first) 
                        + ":" 
                        + to_string(currLoc.second) 
                        + "."
                    );
                }
                fastForward({L')'}, L'(');
                skipBlockOrStatement();
            } else {
                if ((symbol = readChar()) != L'(') {
                    pair<int, int> currLoc = getCurrentLocation();
                    throw runtime_error("Unexpected token '" 
                        + wideStrToStr(symbol) 
                        + "'. At " 
                        + to_string(currLoc.first) 
                        + ":" 
                        + to_string(currLoc.second) 
                        + "."
                    );
                }
                evaluateParentheticalAtom(symbol, lastIfResult);
                if (lastIfResult->toBool()) {
                    evaluateBlockOrStatement();
                } else {
                    skipBlockOrStatement();
                }
            }
            continue;
        } else {
            unreadChar();
            if (elseFound) {
                pair<int, int> currLoc = getCurrentLocation();
                throw runtime_error("Only 1 else statement can go after if. At " 
                    + to_string(currLoc.first) 
                    + ":" 
                    + to_string(currLoc.second) 
                    + "."
                );
            }
            elseFound = true;
            if (lastIfResult->toBool()) {
                skipBlockOrStatement();
            } else {
                evaluateBlockOrStatement();
            }
        }
    }
}

void Interpreter::parseFunction()
{
    wchar_t symbol = readChar();
    wstring functionName;
    if (!parseCharacterSequence(symbol, functionName)) {
        pair<int, int> currLoc = getCurrentLocation();
        throw runtime_error("Failed to parse function name. At " 
            + to_string(currLoc.first) 
            + ":" 
            + to_string(currLoc.second) 
            + "."
        );
    }

    if (functions.has(functionName)) {
        pair<int, int> currLoc = getCurrentLocation();
        throw runtime_error("Function '" 
            + wideStrToStr(functionName) 
            + "' already exists. At " 
            + to_string(currLoc.first) 
            + ":" 
            + to_string(currLoc.second) 
            + "."
        );
    }

    if ((symbol = readChar()) != L'(') {
        pair<int, int> currLoc = getCurrentLocation();
        throw runtime_error("Unexpected token '" 
            + wideStrToStr(symbol) 
            + "'. At " 
            + to_string(currLoc.first) 
            + ":" 
            + to_string(currLoc.second) 
            + "."
        );
    }

    map<int, pair<wstring, shared_ptr<Atom>>> parameters;
    bool hasOptional = false;
    int paramIndex = 0;
    do {
        // function without parameters
        if ((symbol = readChar()) == L')') {
            break;
        }

        wstring argName;
        if (!parseCharacterSequence(symbol, argName)) {
            pair<int, int> currLoc = getCurrentLocation();
            throw runtime_error("Unexpected token '" 
                + wideStrToStr(symbol) 
                + "'. At " 
                + to_string(currLoc.first) 
                + ":" 
                + to_string(currLoc.second) 
                + "."
            );
        }

        if ((symbol = readChar()) == L'=') {
             // initializer for optional parameter
            hasOptional = true;
            parameters[paramIndex] = {argName, evaluateBoolStatement()};
        } else {
            // required parameter
            unreadChar();
            if (hasOptional) {
                pair<int, int> currLoc = getCurrentLocation();
                throw runtime_error("Required parameters cannot go after optional ones. At " 
                    + to_string(currLoc.first) 
                    + ":" 
                    + to_string(currLoc.second) 
                    + "."
                );
            }
            parameters[paramIndex] = {argName, nullptr};
        }

        paramIndex++;
    } while ((symbol = readChar()) == L',');

    if (symbol != L')') {
        pair<int, int> currLoc = getCurrentLocation();
        throw runtime_error("Unexpected token '" 
            + wideStrToStr(symbol) 
            + "'. At " 
            + to_string(currLoc.first) 
            + ":" 
            + to_string(currLoc.second) 
            + "."
        );
    }

    functions.set(functionName, pos, parameters);

    skipBlockOrStatement();
}

void Interpreter::evaluateStatement()
{
    wchar_t symbol;
    if ((symbol = readChar()) == endOfFile) {
        // EOF is achieved
        return;
    }

    // Handle comments
    if (symbol == L'/') {
        if ((symbol = readChar(false, true)) == L'/') {
            // Comment
            fastForward({L'\n'});
            evaluateStatement();
            return;
        } else {
            pair<int, int> currLoc = getCurrentLocation();
            throw runtime_error("Unexpected token '" 
                + wideStrToStr(symbol) 
                + "'. At " 
                + to_string(currLoc.first) 
                + ":" 
                + to_string(currLoc.second) 
                + "."
            );
        }
    }

    if (symbol == L';') {
        // Empty statement
        unreadChar();
        return;
    }

    // handle braces
    if (symbol == L'{' || symbol == L'}') {
        unreadChar();
        return;
    }

    wstring keyWord;
    // handle statements with preceding keywords
    if (parseCharacterSequence(symbol, keyWord)) {

        // PRINT STATEMENT
        if (keyWord == statementPrint) {
            evaluateStatement();
            wcout << lastResult->toString();
            return;
        }
        // END OFPRINT STATEMENT

        // FUNCTION DEFINITION
        if (keyWord == statementFunc) {
            parseFunction();
            dynamicSrc.push_back(L';');
            return;
        }
        // END OF FUNCTION DEFINITION

        // RETURN STATEMENT
        if (keyWord == statementReturn) {
            isReturn = true;
            evaluateStatement();
            return;
        }
        // END OF RETURN STATEMENT

        // BREAK LOOP STATEMENT
        if (keyWord == statementBreak) {
            isBreak = true;
            return;
        }
        // END OF BREAK LOOP STATEMENT

        // IF STATEMENT
        if (keyWord == statementIf) {
            evaluateIfStructure();
            if (!isReturn) {
                dynamicSrc.push_back(L';');
            }
            return;
        }
        // END OF IF STATEMENT

        // FOR STATEMENT
        if (keyWord == statementFor) {
            evaluateForLoop();
            if (!isReturn) {
                dynamicSrc.push_back(L';');
            }
            return;
        }
        // END OF FOR STATEMENT

        // unread keyword
        unreadChar(keyWord.size());
    } else {
        unreadChar();
    }

    lastResult = evaluateBoolStatement();
}

void Interpreter::evaluateStatements()
{
    evaluateStatement();
    wchar_t statementOp;
    while (!isReturn && (statementOp = readChar())) {
        switch (statementOp) {
            case L'{':
            case L'}':
                unreadChar();
                return;
                break;
            // end of statement
            case L',':
            case L';':
                evaluateStatement();
                break;
            default:
                pair<int, int> currLoc = getCurrentLocation();
                throw runtime_error("Unexpected token '" 
                    + wideStrToStr(statementOp) 
                    + "'. At " 
                    + to_string(currLoc.first) 
                    + ":" 
                    + to_string(currLoc.second) 
                    + "."
                );
                break;
        }
    }
}

wstring Interpreter::evaluate(wstring code, int pos)
{
    src = code;
    pos = pos;
    evaluateStatements();
    wchar_t separator;
    while (!isReturn && (separator = readChar())) {
        switch (separator) {
            // start of block
            case L'{':
                evaluateStatements();
                break;
            // end of block
            case L'}':
                evaluateStatements();
                break;
            default:
                pair<int, int> currLoc = getCurrentLocation();
                throw runtime_error("Unexpected token '" 
                    + wideStrToStr(separator) 
                    + "'. At " 
                    + to_string(currLoc.first) 
                    + ":" 
                    + to_string(currLoc.second) 
                    + "."
                );
            break;
        }
    }

    if (isReturn) {
        return lastResult->toString();
    }
    
    return L"";
}
