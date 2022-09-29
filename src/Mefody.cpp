#include "../include/Mefody.h"
#include "../include/tools.h"

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

void Mefody::throwError(string message)
{
    pair<int, int> currLoc = getCurrentLocation();
    throw runtime_error(
        message + " At " 
        + to_string(currLoc.first) 
        + ":" 
        + to_string(currLoc.second) 
        + "."
    );
}

void Mefody::joinAtoms(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right)
{   
    try {
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
    } catch(const exception & e) {
        throwError(e.what());
    }
}

Mefody::Mefody() : Parser()
{
}

Mefody::Variables & Mefody::getStorageRef()
{
    if (stack.size() > 0) {
        return stack.at(stack.size() - 1);
    }
    return variables;
}

bool Mefody::parseDoubleQuotedStringAtom(wchar_t symbol, shared_ptr<Atom> & atom)
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

bool Mefody::parseSingleQuotedStringAtom(wchar_t symbol, shared_ptr<Atom> & atom)
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

bool Mefody::parseKeywordAtom(wstring varName, shared_ptr<Atom> & atom)
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

bool Mefody::parseFunctionCallAtom(wstring varName, shared_ptr<Atom> & atom)
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
    Mefody::Variables functionStack;
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
                throwError("Function required parameter '"
                    + wideStrToStr(funcData.second.at(argumentIndex).first)
                    + "' is missing."
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
        throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
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
        atom = lastResult;
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

bool Mefody::parseNumberLiteralAtom(wchar_t symbol, shared_ptr<Atom> & atom)
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
                    throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
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
            throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
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

bool Mefody::parseStringAccessAtom(wstring varName, const shared_ptr<Atom> key, shared_ptr<Atom> & atom)
{
    if (key->getType() != Atom::typeInt) {
        throwError("Only integer keys can be used for accessing string character.");
    }

    if (key->getInt() < 0) {
        throwError("Negative indexes are not supported.");
    }

    Mefody::Variables storage = getStorageRef();
    if (!storage.has(varName)) {
        throwError("Variable with name '" +  wideStrToStr(varName) + "' does not exist.");
    }

    shared_ptr<Atom> target = storage.get(varName);

    if (target->getString().size() < key->getInt()) {
        throwError("Character at index '" +  to_string(key->getInt()) + "' does not exist.");
    }
    
    // create string atom with one character 
    atom->setString(wstring(1, target->getString().at(key->getInt())));
    atom->setVar(target, key->getInt());
    return true;
}

bool Mefody::parseArrayAccessAtom(wstring varName, shared_ptr<Atom> & atom)
{
    // array element
    wchar_t symbol = readChar();
    if (symbol != L'[') {
        unreadChar();
        return false;
    }

    shared_ptr<Atom> keyAtom = evaluateBoolExpression();
    if (!inVector<wstring>({L"string", L"int", L"double"}, keyAtom->getType())) {
        throwError("Only string and numerical array keys are supported.");
    }

    if ((symbol = readChar()) != L']') {
        throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
    }

    Mefody::Variables storage = getStorageRef();
    // initialize to empty array if not exists
    if (!storage.has(varName)) {
        storage.set(varName,  make_shared<Atom>(map<wstring, shared_ptr<Atom>>{}));
    }
    shared_ptr<Atom> target = storage.get(varName);

    if (target->getType() == Atom::typeString) {
        return parseStringAccessAtom(varName, keyAtom, atom);
    }

    if (target->getType() != Atom::typeArray) {
        throwError("Variable of type" 
            + wideStrToStr(target->getType())
            + " cannot be accessed with an index operator."
        );
    }

    if (!target->issetAt(keyAtom->toString())) {
        target->createAt(
            keyAtom->toString(), 
            make_shared<Atom>(map<wstring, shared_ptr<Atom>>{})
        );
    }

    target = target->elementAt(keyAtom->toString());

    // resolve all possible subsequent access operators
    parseArrayAccessAtom(varName, atom, target);

    // copy variable value to atom value
    *atom = *target;
    // store reference to variable into atom
    atom->setVar(target);
    return true;
}

bool Mefody::parseArrayAccessAtom(wstring varName, shared_ptr<Atom> & atom, shared_ptr<Atom>  & target)
{
    // array element
    wchar_t symbol = readChar();
    if (symbol != L'[') {
        unreadChar();
        return false;
    }

    shared_ptr<Atom> keyAtom = evaluateBoolExpression();
    if (!inVector<wstring>({L"string", L"int", L"double"}, keyAtom->getType())) {
        throwError("Only string and numerical array keys are supported.");
    }

    if ((symbol = readChar()) != L']') {
        throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
    }

    if (target->getType() == Atom::typeString) {
        return parseStringAccessAtom(varName, keyAtom, atom);
    }

    if (target->getType() != Atom::typeArray) {
        throwError("Variable of type" 
            + wideStrToStr(target->getType())
            + " cannot be accessed with an index operator."
        );
    }

    if (!target->issetAt(keyAtom->toString())) {
        target->createAt(
            keyAtom->toString(), 
            make_shared<Atom>(map<wstring, shared_ptr<Atom>>{})
        );
    }

    target = target->elementAt(keyAtom->toString());

    // resolve all possible subsequent access operators
    parseArrayAccessAtom(varName, atom, target);

     // copy variable value to atom value
    *atom = *target;
    // store reference to variable into atom
    atom->setVar(target);
    return true;
}

bool Mefody::parseArrayLiteralAtom(wchar_t symbol, shared_ptr<Atom> & atom)
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
                    throwError("Only string and numeric array keys are supported.");
                }

                symbol = readChar();
            } else {
                throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
            }
        }
    } while (symbol == L',');

    if (symbol != L']') {
        throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
    }

    atom->setArray(array);

    return true;
}

bool Mefody::parseAlphabeticalAtom(wchar_t symbol, shared_ptr<Atom> & atom)
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
        Mefody::Variables & storage = getStorageRef();
        if (!storage.has(varName)) {
            storage.set(varName, make_shared<Atom>());
        }

        // copy variable value to atom value
        *atom = *storage.get(varName);
        // store reference to variable into atom
        atom->setVar(storage.get(varName));
        return true;
    }
    return false;
}

shared_ptr<Atom> Mefody::parseAtom()
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

shared_ptr<Atom> Mefody::evaluateMathBlock()
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
            case L'~': // check against regex
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
                throwError("Unexpected token '" + wideStrToStr(atomOp) + "'.");
                break;
        }
    }
    return result;
}

shared_ptr<Atom> Mefody::evaluateBoolExpression()
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
                    throwError("Unexpected token '"+ wideStrToStr(mathOp) + "' '" + wideStrToStr(symbol) + "'.");
                }
            break;
            case L'!':
                symbol = readChar();
                if (symbol == L'=') {
                    joinAtoms(result, L"!=", evaluateMathBlock());
                } else {
                    throwError("Unexpected token '" + wideStrToStr(mathOp) + "' '" + wideStrToStr(symbol) + "'.");
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
                    throwError("Unexpected token '"+ wideStrToStr(mathOp) + "' '" + wideStrToStr(symbol) + "'.");
                }
            break;
            case L'~': // check against regex
                joinAtoms(result, L"~", evaluateBoolExpression());
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
                throwError("Unexpected token '" + wideStrToStr(mathOp) + "'.");
                break;
        }
    }
    return result;
}

shared_ptr<Atom> Mefody::evaluateBoolStatement()
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
                    throwError("Unexpected token '" + wideStrToStr(booleanOp) + "' '" + wideStrToStr(symbol) + "'.");
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
                    throwError("Unexpected token '" + wideStrToStr(booleanOp) + "' '" + wideStrToStr(symbol) + "'.");
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
                throwError("Unexpected token '" + wideStrToStr(booleanOp) + "'.");
                break;
        }
    }
    return result;
}

bool Mefody::evaluateParentheticalAtom(wchar_t symbol, shared_ptr<Atom> & atom)
{
    if (symbol == L'(') {
        shared_ptr<Atom> subResult = evaluateBoolStatement();
        if (readChar() != L')') {
            throwError("Syntax error. Wrong number of parentheses.");
        }
        if (subResult->getType() == Atom::typeCast) {
            // Type casting
            atom = parseAtom();
            atom->cast(subResult->getCast());
        } else {
            // Subexpression
            atom = subResult;
        }
        return true;
    }
    return false;
}

void Mefody::evaluateForLoop()
{
    wchar_t symbol;
    if ((symbol = readChar()) != L'(') {
        throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
    }

    // Initializer statement
    evaluateStatement();

    if ((symbol = readChar()) != L';') {
        throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
    }

    int conditionPos = pos;
    int postStatementPos = -1;
    int loopBodyPos = -1;

    do {
        evaluateStatement();
        if ((symbol = readChar()) != L';') {
            throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
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

void Mefody::evaluateBlockOrStatement(bool stopOnBreak)
{
    wchar_t symbol;
    if ((symbol = readChar()) != L'{') {
        // evaluate 1 statement
        unreadChar();
        evaluateStatement();
        if ((symbol = readChar()) != L';') {
            throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
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
                    throwError("Unexpected token '" + wideStrToStr(statementOp) + "'.");
                break;
            }
        }
    }
}

void Mefody::evaluateIfStructure()
{
    shared_ptr<Atom> lastIfResult = make_shared<Atom>();
    wchar_t symbol;
    if ((symbol = readChar()) != L'(') {
        throwError("Unexpected token '" + wideStrToStr(symbol) + "'." );
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
                throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
            }
        }

        if ((symbol = readChar(true)) == L'я') {
            for (auto tmp: vector<wchar_t>{L'к', L'щ', L'о'}) {
                symbol = readChar(true);
                if (symbol != tmp) {
                    throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
                }
            }

            if (lastIfResult->toBool()) {
                if ((symbol = readChar()) != L'(') {
                    throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
                }
                fastForward({L')'}, L'(');
                skipBlockOrStatement();
            } else {
                if ((symbol = readChar()) != L'(') {
                    throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
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
                throwError("Only 1 else statement can go after if.");
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

void Mefody::parseFunction()
{
    wchar_t symbol = readChar();
    wstring functionName;
    if (!parseCharacterSequence(symbol, functionName)) {
        throwError("Failed to parse function name." );
    }

    if (functions.has(functionName)) {
        throwError("Function '" + wideStrToStr(functionName) + "' already defined." );
    }

    if ((symbol = readChar()) != L'(') {
        throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
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
            throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
        }

        for (auto const & parameter : parameters) {
            if (parameter.second.first == argName) {
                throwError("Parameter with name '" + wideStrToStr(argName) + "' already exists.");
            }
        }

        if ((symbol = readChar()) == L'=') {
             // initializer for optional parameter
            hasOptional = true;
            parameters[paramIndex] = {argName, evaluateBoolStatement()};
        } else {
            // required parameter
            unreadChar();
            if (hasOptional) {
                throwError("Required parameters cannot go after optional ones.");
            }
            parameters[paramIndex] = {argName, nullptr};
        }

        paramIndex++;
    } while ((symbol = readChar()) == L',');

    if (symbol != L')') {
        throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
    }

    functions.set(functionName, pos, parameters);

    skipBlockOrStatement();
}

void Mefody::evaluateStatement()
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
            throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
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

void Mefody::evaluateStatements()
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
                throwError("Unexpected token '" + wideStrToStr(statementOp) + "'." );
                break;
        }
    }
}

wstring Mefody::evaluate(wstring code, int pos)
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
                throwError("Unexpected token '" + wideStrToStr(separator) + "'." );
            break;
        }
    }

    if (isReturn) {
        return lastResult->toString();
    }
    
    return L"";
}
