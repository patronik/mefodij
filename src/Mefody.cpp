#include "../include/Mefody.h"
#include "../include/tools.h"

vector<wstring> Mefody::castTypes{L"int", L"double", L"string", L"array", L"bool", L"null"};

void Mefody::throwError(string message)
{
    tuple<wstring, int, int> currLoc = getLastLocation();
    throw runtime_error(
        message 
        + " In file: '" 
        + MefodyTools::wideStrToStr(get<0>(currLoc)) 
        +  "'" 
        + " At " 
        + to_string(get<1>(currLoc)) 
        + ":" 
        + to_string(get<2>(currLoc)) 
        + "."
    );
}

Mefody::Mefody() : Parser(), lastResult(nullptr), stack(), coreFuncResolver()
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

bool Mefody::parseCharacterConstAtom(wstring varName, shared_ptr<Atom> & atom)
{
    if (MefodyTools::inVector<wstring>(Mefody::castTypes, varName)) {
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

void Mefody::resolveCoreCall(wstring functionName, shared_ptr<Atom> & atom)
{
    map<int, pair<wstring, shared_ptr<Atom>>> & funcParams = coreFuncResolver.getParams(functionName);

    shared_ptr<Context> functionStack = make_shared<Context>();

    wchar_t symbol = readChar();
    if (symbol != L')') {
        unreadChar();
        // parse arguments
        int argumentIndex = 0;
        do {
            if (funcParams.count(argumentIndex)) {
                functionStack->setVar(funcParams.at(argumentIndex).first, evaluateBoolStatement());
            } else {
                // skip arguments which are not expected by function
                fastForward({L','});
                unreadChar();
            }
            argumentIndex++;
            symbol = readChar();
        } while (symbol == L',');


        // Check required paramaters and set parameters with default values
        while(funcParams.count(argumentIndex)) {
            // No intializer means required parameter is missing
            if (funcParams.at(argumentIndex).second == nullptr) {
                throwError("Function required parameter '"
                    + MefodyTools::wideStrToStr(funcParams.at(argumentIndex).first)
                    + "' is missing."
                );
            } else {
                // Set default value
                functionStack->setVar(
                    funcParams.at(argumentIndex).first, 
                    funcParams.at(argumentIndex).second
                );
            }
            argumentIndex++;
        }
    }

    if (symbol != L')') {
        throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
    }

    coreFuncResolver.resolveCall(functionName, functionStack, atom);
}

bool Mefody::parseFunctionCallAtom(wstring varName, shared_ptr<Atom> & atom)
{
    // function call left parentheses
    wchar_t symbol = readChar();
    if (symbol != L'(') {
        unreadChar();
        return false;
    }

    // resolve core function
    if (coreFuncResolver.hasFunction(varName)) {
        resolveCoreCall(varName, atom);
        return true;
    }

    // check if function exists
    if (!getContext()->hasFunction(varName)) {
        throwError("'" + MefodyTools::wideStrToStr(varName) + "' is not a function.");
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
                    + MefodyTools::wideStrToStr(funcData.second.at(argumentIndex).first)
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
        throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
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
        atom->setAtom(*lastResult);
    }

    // pop function data from stack
    stack.pop_back();

    setState(prevState);

    return true;
}

bool Mefody::parseBinNumberLiteralAtom(shared_ptr<Atom> & atom)
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

bool Mefody::parseHexNumberLiteralAtom(shared_ptr<Atom> & atom) 
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

bool Mefody::parseNumberLiteralAtom(wchar_t symbol, shared_ptr<Atom> & atom)
{
    wstring number{};
    if (MefodyTools::isNumber(symbol)) {
        number.push_back(symbol);

        // Check for other bases
        symbol = readChar(false, true);
        if (number[0] == L'0' && (symbol == L'b' || symbol == L'B')) {
            number.push_back(symbol);
            return parseBinNumberLiteralAtom(atom);
        } else if (number[0] == L'0' && (symbol == L'x' || symbol == L'X')) {
            number.push_back(symbol);
            return parseHexNumberLiteralAtom(atom);
        } else {
            unreadChar(1, true);
        }

        // Decimal int or double
        bool hasDot = false;
        while (symbol = readChar(false, true)) {
            if (MefodyTools::isNumber(symbol))  {
                number.push_back(symbol);
                continue;
            } else if (symbol == L'.') {
                if (hasDot) {
                    throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
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

void Mefody::resolveStringAccess(shared_ptr<Atom> & atom)
{
    shared_ptr<Atom> keyAtom = evaluateBoolExpression();
    if (!MefodyTools::inVector<wstring>({L"int"}, keyAtom->getType())) {
        throwError("Only integer keys are supported.");
    }

    wchar_t symbol;
    if ((symbol = readChar()) != L']') {
        throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
    }

    if (atom->getCharIndex() > -1) {
        throwError("Individual characters cannot be accessed with array access.");
    }

    if (keyAtom->getType() != Atom::typeInt) {
        throwError("Only integer keys can be used for accessing string character.");
    }

    if (keyAtom->getInt() < 0) {
        throwError("Negative indexes are not supported.");
    }

    if (atom->getString().size() < keyAtom->getInt()) {
        throwError("Character at index '" +  to_string(keyAtom->getInt()) + "' does not exist.");
    }

    // trasform string to single char string
    atom->setString(wstring(1, atom->getString().at(keyAtom->getInt())));
    atom->setCharIndex(keyAtom->getInt());
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

    if (atom->getVar()->getType() != Atom::typeArray) {
        atom->getVar()->setArray(map<wstring, shared_ptr<Atom>>{});
    }

    wstring arrayKey;
    if (implicitKey) {
        arrayKey = to_wstring(atom->getVar()->getArrayNextIndex());
        atom->getVar()->setArrayNextIndex(atom->getVar()->getArrayNextIndex() + 1);
    } else {
        shared_ptr<Atom> keyAtom = evaluateBoolExpression();
        if (!MefodyTools::inVector<wstring>({L"string", L"int"}, keyAtom->getType())) {
            throwError("Only string and integer array keys are supported.");
        }

        wchar_t symbol;
        if ((symbol = readChar()) != L']') {
            throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
        }
        arrayKey = keyAtom->toString();
    }

    if (!atom->getVar()->issetAt(arrayKey)) {
        atom->getVar()->createAt(arrayKey, make_shared<Atom>());
    }

    // Backup pointer to variable
    auto varPtr = atom->getVar();

    // Copy element state to atom
    atom->setAtom(*varPtr->elementAt(arrayKey));

    // Update pointer to variable
    atom->setVar(varPtr->elementAt(arrayKey));
}

void Mefody::resolveMemberAccess(shared_ptr<Atom> & atom)
{
    wstring memberName{};
    if (!parseCharacterSequence(readChar(), memberName)) {
        throw runtime_error("Unexpected atom member name.");
    }
    atom->resolveMember(memberName);
}

void Mefody::resolveAtom(shared_ptr<Atom> & atom)
{
     wchar_t symbol = readChar();
     if (symbol == L'[') {
        if (atom->getType() == Atom::typeString) {
            resolveStringAccess(atom);
        } else {
            resolveArrayAccess(atom);
            // recursevily resolve the whole chain
            resolveAtom(atom);
        }
     } else if (symbol == L'.') {
        resolveMemberAccess(atom);
        // recursevily resolve the whole chain
        resolveAtom(atom);
     } else {
        unreadChar();
     }
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
                } else {
                    throwError("Only string and integer array keys are supported.");
                }

                symbol = readChar();
            } else {
                throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
            }
        }
    } while (symbol == L',');

    if (symbol != L']') {
        throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
    }

    atom->setArray(array);

    return true;
}

bool Mefody::parseAlphabeticalAtom(wchar_t symbol, shared_ptr<Atom> & atom)
{
    // alphabetical atom
    wstring varName{};
    if (parseCharacterSequence(symbol, varName)) {
        // try to recognize keyword 
        if (parseCharacterConstAtom(varName, atom)) {
            return true;
        }

        // check if sequence is reserved 
        if (MefodyTools::inVector<wstring>(reservedKeywords, varName)) {
            throwError("This name '" + MefodyTools::wideStrToStr(varName) + "' is reserved.");
        }

        // try to process function call atom
        if (parseFunctionCallAtom(varName, atom)) {
            return true;
        }

        // variable atom
        shared_ptr<Context> storage = getContext();
        if (!storage->hasVar(varName)) {
            throwError("Variable '" + MefodyTools::wideStrToStr(varName) + "' is not defined.");
        }

        // copy variable state to atom 
        atom->setAtom(*storage->getVar(varName));
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

    parseParentheticalAtom(atomChar, atom)
    || parseAlphabeticalAtom(atomChar, atom)
    || parseArrayLiteralAtom(atomChar, atom)
    || parseNumberLiteralAtom(atomChar, atom)
    || parseSingleQuotedStringAtom(atomChar, atom)
    || parseDoubleQuotedStringAtom(atomChar, atom);

    resolveAtom(atom);

    if (preOperator.size()) {
        atom->preOperator(preOperator);
    }

    if (boolInversion) {
        atom->preOperator(L"!");
    }

    return atom;
}

shared_ptr<Atom> Mefody::evaluateMathExpression()
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
            case L'%':
                joinAtoms(result, L"%", parseAtom());
            break;
            case L'+':
                symbol = readChar();
                if (symbol == L'+') {
                    result->postOperator(L"++");
                } else if (symbol == L'=') {
                    joinAtoms(result, L"+", evaluateBoolStatement());
                    assignToAtom(result, L"=", result);
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
                    assignToAtom(result, L"=", result);
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
                    assignToAtom(result, L"=", evaluateBoolStatement());
                }
                break;
            // Lower lever operators
            case L'!': // boolean not
            case L'&': // start of boolean and
            case L'>': // less than
            case L'<': // greater than
            case L'|': // boolean "or" ||
            case L'~': // check against regex
            // end of argument or statement
            case L',':
            // end of subexpression
            case L')':
            // end of statement
            case L';':
            // array value parsed
            case L']':
            // separator in range loop
            case L':':
                // start of statement block
                unreadChar();
                return result;
                break;
            default:
                throwError("Unexpected token '" + MefodyTools::wideStrToStr(atomOp) + "'.");
                break;
        }
    }
    return result;
}

shared_ptr<Atom> Mefody::evaluateBoolExpression()
{
    shared_ptr<Atom> result = evaluateMathExpression();
    wchar_t mathOp;
    wchar_t symbol;
    while (mathOp = readChar(true)) {
        switch (mathOp) {
            case L'+':
                joinAtoms(result, L"+", evaluateMathExpression());
            break;
            case L'-':
                joinAtoms(result, L"-", evaluateMathExpression());
            break;
            case L'=':
                symbol = readChar();
                if (symbol == L'=') {
                    joinAtoms(result, L"==", evaluateMathExpression());
                } else if (symbol == L'>')  {
                    // key-val separator
                    unreadChar(2);
                    return result;
                    break;
                } else {
                    throwError("Unexpected token '"+ MefodyTools::wideStrToStr(mathOp) + "' '" + MefodyTools::wideStrToStr(symbol) + "'.");
                }
            break;
            case L'!':
                symbol = readChar();
                if (symbol == L'=') {
                    joinAtoms(result, L"!=", evaluateMathExpression());
                } else {
                    throwError("Unexpected token '" + MefodyTools::wideStrToStr(mathOp) + "' '" + MefodyTools::wideStrToStr(symbol) + "'.");
                }
            break;
            case L'>':
                symbol = readChar();
                if (symbol == L'=') {
                    joinAtoms(result, L">=", evaluateMathExpression());
                } else {
                    unreadChar();
                    joinAtoms(result, L">", evaluateMathExpression());
                }
            break;
            case L'<':
                symbol = readChar();
                if (symbol == L'=') {
                    joinAtoms(result, L"<=", evaluateMathExpression());
                } else {
                    unreadChar();
                    joinAtoms(result, L"<", evaluateMathExpression());
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
            // separator in range loop
            case L':':
                unreadChar();
                // return result from recursive call
                return result;
                break;
            default:
                throwError("Unexpected token '" + MefodyTools::wideStrToStr(mathOp) + "'.");
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
                    joinAtoms(result, L"||", evaluateBoolExpression());
                } else {
                    throwError("Unexpected token '" + MefodyTools::wideStrToStr(booleanOp) + "' '" + MefodyTools::wideStrToStr(symbol) + "'.");
                }
                break;
            case L'&':
                symbol = readChar();
                if (symbol == L'&') {
                    joinAtoms(result, L"&&", evaluateBoolExpression());
                } else {
                    throwError("Unexpected token '" + MefodyTools::wideStrToStr(booleanOp) + "' '" + MefodyTools::wideStrToStr(symbol) + "'.");
                }
                break;
            // end of argument
            case L',':
            // end of subexpression
            case L')':
            // end of statement
            case L';':
            // separator in range loop
            case L':':
                unreadChar();
                // return result from recursive call
                return result;
                break;
            default:
                throwError("Unexpected token '" + MefodyTools::wideStrToStr(booleanOp) + "'.");
                break;
        }
    }
    return result;
}

bool Mefody::parseParentheticalAtom(wchar_t symbol, shared_ptr<Atom> & atom)
{
    if (symbol == L'(') {
        shared_ptr<Atom> subExpr = evaluateBoolStatement();
        if (readChar() != L')') {
            throwError("Syntax error. Wrong number of parentheses.");
        }
        if (subExpr->getType() == Atom::typeCast) {
            // Type casting
            atom = parseAtom();
            atom->cast(subExpr->getCast());
        } else {
            // atom is a result of subexpression
            atom = subExpr;
        }
        return true;
    }
    return false;
}

void Mefody::evaluateWhileLoop(int firstStmtPos)
{
    int loopBodyPos = pos;

    while (lastResult->toBool()) {        
        shared_ptr<Context> iterationStack = make_shared<Context>();
        iterationStack->setParent(getContext());
        // push function data onto stack
        stack.push_back(iterationStack);

        evaluateBlockOrStatement(true);

        // pop iteration stack
        stack.pop_back();

        if (isBreak || isReturn) {
            break;
        }

        pos = firstStmtPos;
        evaluateStatement();
        
        pos = loopBodyPos;
    }

    pos = firstStmtPos;
    fastForward({L')'}, L'(');
    skipBlockOrStatement();

    isBreak = false;

    // pop loop stack
    stack.pop_back();
}

void Mefody::evaluateRangeLoop(int firstStmtPos)
{
    if (lastResult->getVar() == nullptr) {
        throwError("Initial statement should resolve to variable.");
    }
    auto elementVar = lastResult->getVar();

    // Container statement
    evaluateStatement();

    if (lastResult->getVar() == nullptr 
        || lastResult->getVar()->getType() != Atom::typeArray
    ) {
        throwError("Separator must be followed by array.");
    }
    auto arrayVar = lastResult->getVar();

    wchar_t symbol;
    if ((symbol = readChar()) != L')') {
        throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
    }

    int loopBodyPos = -1;

    for (auto elem: arrayVar->getArray()) {
        elementVar->setArray({
            {L"0", make_shared<Atom>(elem.first)},
            {L"1", elem.second}
        });

        shared_ptr<Context> iterationStack = make_shared<Context>();
        iterationStack->setParent(getContext());
        // push function data onto stack
        stack.push_back(iterationStack);

        if (loopBodyPos == -1) {
            loopBodyPos = pos;
        } 

        evaluateBlockOrStatement(true);

        // pop iteration stack
        stack.pop_back();

        if (isBreak || isReturn) {
            break;
        }

        pos = loopBodyPos;
    }

    pos = firstStmtPos;
    fastForward({L')'}, L'(');
    skipBlockOrStatement();

    isBreak = false;

    // pop loop stack
    stack.pop_back();
}

void Mefody::evaluateForLoop()
{
    shared_ptr<Context> loopStack = make_shared<Context>();
    loopStack->setParent(getContext());
    // push function data onto stack
    stack.push_back(loopStack);

    wchar_t symbol;
    if ((symbol = readChar()) != L'(') {
        throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
    }

    int firstStmtPos = pos;

    // Initializer statement
    evaluateStatement();

    // Range loop
    if ((symbol = readChar()) == L':') {
        evaluateRangeLoop(firstStmtPos);
        return;
    } else {
        unreadChar();
    }

    // While loop
    if ((symbol = readChar()) == L')') {
        evaluateWhileLoop(firstStmtPos);
        return;
    } else {
        unreadChar();
    }

    if ((symbol = readChar()) != L';') {
        throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
    }

    // For loop
    int conditionPos = pos;
    int postStatementPos = -1;
    int loopBodyPos = -1;

    do {
        evaluateStatement();
        if ((symbol = readChar()) != L';') {
            throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
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

        shared_ptr<Context> iterationStack = make_shared<Context>();
        iterationStack->setParent(getContext());
        // push function data onto stack
        stack.push_back(iterationStack);

        evaluateBlockOrStatement(true);

        // pop iteration stack
        stack.pop_back();

        if (isBreak || isReturn) {
            break;
        }

        // Evaluate first post statement
        pos = postStatementPos;
        evaluateStatement();

        // Evaluate all comma separated post statements
        while ((symbol = readChar()) == L',') {
            evaluateStatement();
        } 
        unreadChar();

        // Prepare for next iteration
        pos = conditionPos;
    } while(true);

    pos = conditionPos;
    fastForward({L')'}, L'(');
    skipBlockOrStatement();

    isBreak = false;

    // pop loop stack
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
            throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
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
                    throwError("Unexpected token '" + MefodyTools::wideStrToStr(statementOp) + "'.");
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
        throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'." );
    }

    parseParentheticalAtom(symbol, lastIfResult);

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
        
        bool evalElse = true, evalElseIf = true;
        
        // Check for else
        int i = 0;
        while (i < statementElse.size()) {
            if ((symbol = readChar()) != statementElse.at(i)) {
                evalElse = false;
                unreadChar(i + 1);
                break;
            }
            i++;
        }

        if (!evalElse) {
            break;
        } else {
            // Check for else if
            int j = 0;
            while (j < statementIf.size()) {
                if ((symbol = readChar()) != statementIf.at(j)) {
                    evalElseIf = false;
                    unreadChar(j + 1);
                    break;
                }
                j++;
            }

            if (evalElseIf) {
                // Evaluate else if
                if (lastIfResult->toBool()) {
                    if ((symbol = readChar()) != L'(') {
                        throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
                    }
                    fastForward({L')'}, L'(');
                    skipBlockOrStatement();
                } else {
                    if ((symbol = readChar()) != L'(') {
                        throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
                    }
                    parseParentheticalAtom(symbol, lastIfResult);
                    if (lastIfResult->toBool()) {
                        evaluateBlockOrStatement();
                    } else {
                        skipBlockOrStatement();
                    }
                }
                continue;
            } else {
                // Evaluate else
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

void Mefody::parseVariable(bool isConst) 
{
    // Backup pos
    int prevPos = pos;

    wchar_t symbol = readChar();
    wstring varName;
    if (!parseCharacterSequence(symbol, varName)) {
        throwError("Failed to parse variable name.");
    }

    if (getContext()->hasOwnVar(varName)) {
        throwError("Variable '" + MefodyTools::wideStrToStr(varName) + "' already defined." );
    }

    if (MefodyTools::inVector<wstring>(reservedKeywords,varName)) {
        throwError("This name '" + MefodyTools::wideStrToStr(varName) + "' is reserved." );
    }

    auto newVariable = make_shared<Atom>();
    
    if (isConst) {
        newVariable->setIsConst();
    }

    getContext()->setVar(varName, newVariable);

    pos = prevPos;

    evaluateStatement();

    if ((symbol = readChar()) == L',') {
        // recursively declare all variables
        parseVariable(isConst);
    } else {
        unreadChar();
    }
}

void Mefody::parseFunction()
{
    wchar_t symbol = readChar();
    wstring functionName;
    if (!parseCharacterSequence(symbol, functionName)) {
        throwError("Failed to parse function name." );
    }

    if (coreFuncResolver.hasFunction(functionName)) {
        throwError("Function '" + MefodyTools::wideStrToStr(functionName) + "' is core function." );
    }

    if (getContext()->hasOwnFunction(functionName)) {
        throwError("Function '" + MefodyTools::wideStrToStr(functionName) + "' already defined." );
    }

    if (MefodyTools::inVector<wstring>(reservedKeywords,functionName)) {
        throwError("This name '" + MefodyTools::wideStrToStr(functionName) + "' is reserved." );
    }

    if ((symbol = readChar()) != L'(') {
        throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
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
            throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
        }

        for (auto const & parameter : parameters) {
            if (parameter.second.first == argName) {
                throwError("Parameter with name '" + MefodyTools::wideStrToStr(argName) + "' already exists.");
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
        throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
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
            throwError("Unexpected token '" + MefodyTools::wideStrToStr(symbol) + "'.");
        }
    }

    // Empty statement
    if (symbol == L';') {
        // Last result is set to emtpy atom
        lastResult->setAtom(Atom());
        // Skip to next statement
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
            return;
        }
        // END OF VARIABLE DEFINITION

        // CONST VARIABLE DEFINITION
        if (keyWord == statementConst) {
            parseVariable(true);
            return;
        }
        // END OF CONST VARIABLE DEFINITION

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
    wchar_t sep;
    while (!isReturn && (sep = readChar())) {
        switch (sep) {
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
                throwError("Unexpected token '" + MefodyTools::wideStrToStr(sep) + "'.");
                break;
        }
    }
}

wstring Mefody::evaluate()
{
    try {
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
                    throwError("Unexpected token '" + MefodyTools::wideStrToStr(separator) + "'." );
                break;
            }
        }

        if (isReturn) {
            return lastResult->toString();
        }
        
    } catch(const exception & e) {
        throwError(e.what());
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