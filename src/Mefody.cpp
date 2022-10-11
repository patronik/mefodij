#include "../include/Mefody.h"
#include "../include/tools.h"

void Mefody::throwError(string message)
{
    tuple<wstring, int, int> currLoc = getLastLocation();
    throw runtime_error(
        message 
        + " In file: '" 
        + wideStrToStr(get<0>(currLoc)) 
        +  "'" 
        + " At " 
        + to_string(get<1>(currLoc)) 
        + ":" 
        + to_string(get<2>(currLoc)) 
        + "."
    );
}

Mefody::Mefody() : Parser(), lastResult(nullptr), stack()
{
    context = make_shared<Context>();
}

tuple<int, wstring, wstring, bool, bool, shared_ptr<Atom>> Mefody::getState()
{
    return tuple<int, wstring, wstring, bool, bool, shared_ptr<Atom>>{pos, src, dynamicSrc, isReturn, isBreak, lastResult};
}

void Mefody::setState(const tuple<int, wstring, wstring, bool, bool, shared_ptr<Atom>> & state)
{
    lastResult = get<5>(state);
    isBreak = get<4>(state);
    isReturn = get<3>(state);
    dynamicSrc = get<2>(state);
    src = get<1>(state);
    pos = get<0>(state);
}

shared_ptr<Context> Mefody::getContext()
{
    if (stack.size() > 0) {
        return stack.at(stack.size() - 1);
    }
    return context;
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
    // function call left parentheses
    wchar_t symbol = readChar();
    if (symbol != L'(') {
        unreadChar();
        return false;
    }

    // check if function exists
    if (!getContext()->hasFunction(varName)) {
        unreadChar(); // unread (
        return false;
    }

    pair<int, map<int, pair<wstring, shared_ptr<Atom>>>> & funcData = getContext()->getFunction(varName);
    shared_ptr<Context> functionStack = make_shared<Context>();
    symbol = readChar();
    if (symbol != L')') {
        unreadChar();
        // parse arguments
        int argumentIndex = 0;
        do {
            if (funcData.second.count(argumentIndex)) {
                functionStack->setVar(funcData.second.at(argumentIndex).first, evaluateBoolStatement());
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
                functionStack->setVar(
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
        atom = lastResult;
    }

    // pop function data from stack
    stack.pop_back();

    setState(prevState);

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

void Mefody::resolveStringAccess(const shared_ptr<Atom> key, shared_ptr<Atom> & atom)
{
    if (atom->getCharIndex() > -1) {
        throwError("Individual characters cannot be accessed with array access.");
    }

    if (key->getType() != Atom::typeInt) {
        throwError("Only integer keys can be used for accessing string character.");
    }

    if (key->getInt() < 0) {
        throwError("Negative indexes are not supported.");
    }

    if (atom->getString().size() < key->getInt()) {
        throwError("Character at index '" +  to_string(key->getInt()) + "' does not exist.");
    }

    // trasform string to single char string
    atom->setString(wstring(1, atom->getString().at(key->getInt())));
    atom->setCharIndex(key->getInt());
}

void Mefody::resolveArrayAccess(shared_ptr<Atom> & atom) 
{
    int implicitKey = false;
    wchar_t symbol;
    if ((symbol = readChar()) == L']') {
        implicitKey = true;
    } else {
        unreadChar();
    }

    wstring arrayKey;
    if (implicitKey) {
        if (atom->getType() == Atom::typeString) {
            throwError("Implicit key are not allowed for string accessing.");
        }
        arrayKey = to_wstring(atom->getArrayNextIndex());
        atom->getVar()->setArrayNextIndex(atom->getArrayNextIndex() + 1);
    } else {
        shared_ptr<Atom> keyAtom = evaluateBoolExpression();
        if (!inVector<wstring>({L"string", L"int", L"double"}, keyAtom->getType())) {
            throwError("Only string and numerical array keys are supported.");
        }

        wchar_t symbol;
        if ((symbol = readChar()) != L']') {
            throwError("Unexpected token '" + wideStrToStr(symbol) + "'.");
        }

        if (atom->getType() == Atom::typeString) {
            return resolveStringAccess(keyAtom, atom);
        }
        arrayKey = keyAtom->toString();
    }

    if (atom->getVar()->getType() != Atom::typeArray) {
        atom->getVar()->setArray(map<wstring, shared_ptr<Atom>>{});
    }

    if (!atom->getVar()->issetAt(arrayKey)) {
        atom->getVar()->createAt(arrayKey, make_shared<Atom>());
    }

    atom->setAtom(atom->getVar()->elementAt(arrayKey));
    atom->setVar(atom->getVar()->elementAt(arrayKey));
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
    atom->setArrayNextIndex(implicitKey + 1);

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

        // variable atom
        shared_ptr<Context> storage = getContext();
        if (!storage->hasVar(varName)) {
            throwError("Variable '" + wideStrToStr(varName) + "' is not defined.");
        }

        // copy variable value to atom value
        atom->setAtom(storage->getVar(varName));
        // store reference to variable into atom
        atom->setVar(storage->getVar(varName));
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
            case L'[':
                resolveArrayAccess(result);
            break;
            case L'&':
                symbol = readChar();
                if (symbol == L'&') {
                    // Lower lever operator
                    unreadChar(2);
                    return result;
                } else {
                    unreadChar();
                    joinAtoms(result, L"&", parseAtom());
                }
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
            // atom is a result of subexpression
            atom = subResult;
        }
        return true;
    }
    return false;
}

void Mefody::evaluateForLoop()
{
    shared_ptr<Context> loopStack = make_shared<Context>();
    loopStack->setParent(getContext());
    // push function data onto stack
    stack.push_back(loopStack);

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

    // pop function data from stack
    stack.pop_back();
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

        bool elseFound = false;
        while (!isReturn) {
            if (readChars(true, false, 3) != L"або") {
                unreadChar(3);
                break;
            }

            if (readChars(true, false, 5) == L"умова") {
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
                unreadChar(5);
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
}

void Mefody::parseVariable() 
{
    // Backup pos
    int prevPos = pos;

    wchar_t symbol = readChar();
    wstring varName;
    if (!parseCharacterSequence(symbol, varName)) {
        throwError("Failed to parse variable name.");
    }

    if (getContext()->hasOwnVar(varName)) {
        throwError("Variable '" + wideStrToStr(varName) + "' already defined." );
    }

    if (getContext()->hasOwnFunction(varName)) {
        throwError("This name '" + wideStrToStr(varName) + "' is already used by function." );
    }

    if (inVector<wstring>(reservedKeywords,varName)) {
        throwError("This name '" + wideStrToStr(varName) + "' is reserved." );
    }

    getContext()->setVar(varName, make_shared<Atom>());

    pos = prevPos;
}

void Mefody::parseFunction()
{
    wchar_t symbol = readChar();
    wstring functionName;
    if (!parseCharacterSequence(symbol, functionName)) {
        throwError("Failed to parse function name." );
    }

    if (getContext()->hasOwnFunction(functionName)) {
        throwError("Function '" + wideStrToStr(functionName) + "' already defined." );
    }

    if (getContext()->hasOwnVar(functionName)) {
        throwError("This name '" + wideStrToStr(functionName) + "' is already used by variable." );
    }

    if (inVector<wstring>(reservedKeywords,functionName)) {
        throwError("This name '" + wideStrToStr(functionName) + "' is reserved." );
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

    getContext()->setFunction(functionName, pos, parameters);

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

        // IMPORT STATEMENT
        if (keyWord == statementImport) {
            evaluateStatement();
            if ((symbol = readChar()) != L';') {
                unreadChar();
            }
            insertSource(lastResult->toString());
            evaluateStatement();
            return;
        }
        // END OF IMPORT STATEMENT

        // PRINT STATEMENT
        if (keyWord == statementPrint) {
            evaluateStatement();
            wcout << lastResult->toString();
            return;
        }
        // END OF PRINT STATEMENT

        // VARIABLE DEFINITION
        if (keyWord == statementLem) {
            parseVariable();
            evaluateStatement();
            return;
        }
        // END OF VARIABLE DEFINITION

        // FUNCTION DEFINITION
        if (keyWord == statementFunc) {
            parseFunction();
            dynamicSrc.push_back(L';');
            return;
        }
        // END OF FUNCTION DEFINITION

        // RETURN STATEMENT
        if (keyWord == statementExit) {
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

wstring Mefody::evaluate()
{
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

wstring Mefody::evaluateFile(string filename)
{
    wstring wfilename(filename.begin(), filename.end()); 
    return evaluateFile(wfilename);
}

wstring Mefody::evaluateFile(wstring wfilename)
{
    insertSource(wfilename);
    return evaluate();
}