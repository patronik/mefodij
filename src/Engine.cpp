#include "../include/Engine.h"
#include "../include/Keyword.h"
#include "../include/tools.h"

namespace Mefodij {

    Engine::Engine() : AtomParser()
    {
        context = make_shared<Context>();
    }

    void Engine::throwError(string message)
    {
        tuple<wstring, int, int> currLoc = getLastLocation();

        string fileLoc = "";
        if (get<0>(currLoc) != L"") {
            fileLoc = " In file: '" 
            + Tools::wideStrToStr(get<0>(currLoc)) 
            +  "'";
        }

        throw runtime_error(
            message 
            + fileLoc
            + (fileLoc != "" ? " at ": " At ") 
            + to_string(get<1>(currLoc)) 
            + ":" 
            + to_string(get<2>(currLoc)) 
            + "."
        );
    }

    tuple<int, wstring, wstring, bool, bool, shared_ptr<Atom>> Engine::getState()
    {
        return tuple<int, wstring, wstring, bool, bool, shared_ptr<Atom>>{
            pos, 
            src, 
            dynamicSrc, 
            isReturn, 
            isBreak, 
            lastResult
        };
    }

    void Engine::setState(const tuple<int, wstring, wstring, bool, bool, shared_ptr<Atom>> & state)
    {
        pos = get<0>(state);
        src = get<1>(state);
        dynamicSrc = get<2>(state);
        isReturn = get<3>(state);
        isBreak = get<4>(state);
        lastResult = get<5>(state);
    }

    shared_ptr<Context> Engine::getContext()
    {
        if (stack.size() > 0) {
            return stack.at(stack.size() - 1);
        }
        return context;
    }

    shared_ptr<Context> Engine::prepareCallStack(map<int, tuple<wstring, shared_ptr<Atom>, bool>> params)
    {
        shared_ptr<Context> functionStack = make_shared<Context>();

        int argumentIndex = 0;
        
        wchar_t symbol = readChar();
        if (symbol != L')') {
            unreadChar();
            // parse arguments
            do {
                if (params.count(argumentIndex)) {
                    auto funcVar = evaluateBoolStatement();
                    
                    if (get<2>(params.at(argumentIndex))) {
                        // pass by reference
                        if (funcVar->getVarRef() == nullptr) {
                            throw runtime_error("Only variables can be passed by reference.");
                        }
                        funcVar = funcVar->getVarRef();
                    }  
                
                    functionStack->setVar(
                        get<0>(params.at(argumentIndex)), 
                        funcVar
                    );

                } else {
                    // skip arguments which are not expected by function
                    fastForward({L','});
                    unreadChar();
                }
                argumentIndex++;
                symbol = readChar();
            } while (symbol == L',');
        } 

        // check and set default params
        while(params.count(argumentIndex)) {
            // No intializer means required parameter is missing
            if (get<1>(params.at(argumentIndex)) == nullptr) {
                throw runtime_error("Function required parameter '"
                    + Tools::wideStrToStr(get<0>(params.at(argumentIndex)))
                    + "' is missing."
                );
            } else {
                // Set default value
                functionStack->setVar(
                    get<0>(params.at(argumentIndex)), 
                    get<1>(params.at(argumentIndex))
                );
            }
            argumentIndex++;
        }

        if (symbol != L')') {
            throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
        }

        return functionStack;
    }

    void Engine::resolveCoreFunctionCall(wstring functionName, shared_ptr<Atom> & atom)
    {
        map<int, tuple<wstring, shared_ptr<Atom>, bool>> & funcParams = coreResolver.getParams(functionName);

        shared_ptr<Context> functionStack = prepareCallStack(funcParams);

        coreResolver.resolveCall(functionName, functionStack, atom);
    }

    void Engine::resolveStringAccess(shared_ptr<Atom> & atom)
    {
        shared_ptr<Atom> keyAtom = evaluateBoolExpression();
        if (!Tools::inVector<wstring>({Keyword::typeInt}, keyAtom->getType())) {
            throw runtime_error("Only integer keys are supported.");
        }

        wchar_t symbol;
        if ((symbol = readChar()) != L']') {
            throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
        }

        if (atom->getCharIndex() > -1) {
            throw runtime_error("Individual characters cannot be accessed with array access.");
        }

        if (keyAtom->getType() != Keyword::typeInt) {
            throw runtime_error("Only integer keys can be used for accessing string character.");
        }

        if (keyAtom->getInt() < 0) {
            throw runtime_error("Negative indexes are not supported.");
        }

        if (atom->getString().size() < keyAtom->getInt()) {
            throw runtime_error("Character at index '" +  to_string(keyAtom->getInt()) + "' does not exist.");
        }

        // trasform string to single char string
        atom->setString(wstring(1, atom->getString().at(keyAtom->getInt())));
        atom->setCharIndex(keyAtom->getInt());
    }

    void Engine::resolveArrayAccess(shared_ptr<Atom> & atom) 
    {
        int implicitKey = false;
        wchar_t symbol;
        if ((symbol = readChar()) == L']') {
            implicitKey = true;
        } else {
            unreadChar();
        }

        if (atom->getVarRef()->getType() != Keyword::typeArray) {
            atom->getVarRef()->setArray(map<wstring, shared_ptr<Atom>, Tools::arrayCmp>{});
        }

        wstring arrayKey;
        if (implicitKey) {
            arrayKey = Tools::to_wstring(atom->getVarRef()->getArrayNextIndex());
            atom->getVarRef()->setArrayNextIndex(atom->getVarRef()->getArrayNextIndex() + 1);
        } else {
            shared_ptr<Atom> keyAtom = evaluateBoolExpression();
            if (!Tools::inVector<wstring>({Keyword::typeString, Keyword::typeInt}, keyAtom->getType())) {
                throw runtime_error("Only string and integer array keys are supported.");
            }

            wchar_t symbol;
            if ((symbol = readChar()) != L']') {
                throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
            }
            arrayKey = keyAtom->toString();
        }

        if (!atom->getVarRef()->issetAt(arrayKey)) {
            atom->getVarRef()->setElementAt(
                arrayKey, make_shared<Atom>(nullptr)
            );
        }

        // Backup pointer to variable
        auto varPtr = atom->getVarRef();

        // Copy element state to atom
        atom->setAtom(*varPtr->elementAt(arrayKey));

        // Update pointer to variable
        atom->setVarRef(varPtr->elementAt(arrayKey));
    }

    void Engine::resolveMemberAccess(shared_ptr<Atom> & atom)
    {
        wstring memberName{};
        if (!parseCharacterSequence(readChar(), memberName)) {
            throw runtime_error("Unexpected member name.");
        }
        atom->resolveMember(memberName);
    }

    void Engine::resolveAtomAssignment(shared_ptr<Atom> & atom)
    {
        // Resolve assignment
        wchar_t symbol = readChar();
        if (symbol == L'=') {
            symbol = readChar();
            if (symbol == L'=') {
                // equality
                unreadChar(2);
                return;
            } else if (symbol == L'>')  {
                // key-val separator
                unreadChar(2);
                return;
            } else {
                unreadChar();
                // execute assignment statement
                assignToAtom(atom, L"=", evaluateBoolStatement());
            }
        } else if (symbol == L'+') {
            symbol = readChar();
            if (symbol == L'=') {
                joinAtoms(atom, L"+", evaluateBoolStatement());
                assignToAtom(atom, L"=", atom);
            } else {
                unreadChar(2);
                return;
            }
        } else if (symbol == L'-') {
            symbol = readChar();
            if (symbol == L'=') {
                joinAtoms(atom, L"-", evaluateBoolStatement());
                assignToAtom(atom, L"=", atom);
            } else {
                unreadChar(2);
                return;
            }
        } else {
            unreadChar();
        }
    }

    void Engine::resolveAtomAccess(shared_ptr<Atom> & atom)
    {
        wchar_t symbol = readChar();
        // Resolve element/member access
        if (symbol == L'[') {
            if (atom->getType() == Keyword::typeString) {
                resolveStringAccess(atom);
            } else {
                resolveArrayAccess(atom);
                // recursevily resolve the whole chain
                resolveAtomAccess(atom);
            }
        } else if (symbol == L'.') {
            resolveMemberAccess(atom);
            // recursevily resolve the whole chain
            resolveAtomAccess(atom);
        } else {
            unreadChar();
        }
    }

    shared_ptr<Atom> Engine::evaluateMathExpression()
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
                    } else {
                        // Lower lever operator
                        unreadChar(2);
                        return result;
                    }
                break;
                default:
                    unreadChar();
                    return result;
            }
        }
        return result;
    }

    shared_ptr<Atom> Engine::evaluateBoolExpression()
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
                        throw runtime_error("Unexpected token '"+ Tools::wideStrToStr(mathOp) + "' '" + Tools::wideStrToStr(symbol) + "'.");
                    }
                break;
                case L'!':
                    symbol = readChar();
                    if (symbol == L'=') {
                        joinAtoms(result, L"!=", evaluateMathExpression());
                    } else {
                        throw runtime_error("Unexpected token '" + Tools::wideStrToStr(mathOp) + "' '" + Tools::wideStrToStr(symbol) + "'.");
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
                default:
                    unreadChar();
                    return result;
            }
        }
        return result;
    }

    shared_ptr<Atom> Engine::evaluateBoolStatement()
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
                        throw runtime_error("Unexpected token '" 
                            + Tools::wideStrToStr(booleanOp) + "' '" 
                            + Tools::wideStrToStr(symbol) + "'."
                        );
                    }
                    break;
                case L'&':
                    symbol = readChar();
                    if (symbol == L'&') {
                        joinAtoms(result, L"&&", evaluateBoolExpression());
                    } else {
                        throw runtime_error("Unexpected token '" 
                            + Tools::wideStrToStr(booleanOp) + "' '" 
                            + Tools::wideStrToStr(symbol) + "'."
                        );
                    }
                    break;
                default:
                    unreadChar();
                    return result;
            }
        }
        return result;
    }

    

    void Engine::evaluateWhileLoop(int firstStmtPos)
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

    void Engine::evaluateRangeLoop(int firstStmtPos)
    {
        auto elementVar = lastResult->getVarRef();
        elementVar->setArray(map<wstring, shared_ptr<Atom>, Tools::arrayCmp>{});

        if (elementVar == nullptr) {
            throw runtime_error("Initial statement should resolve to variable.");
        }

        // Container statement
        evaluateStatement();

        if (lastResult->getType() != Keyword::typeArray) {
            throw runtime_error("Separator must be followed by an array.");
        }

        wchar_t symbol;
        if ((symbol = readChar()) != L')') {
            throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
        }

        int loopBodyPos = -1;

        auto array = lastResult->getArray();
        for (auto elem: array) {
            // Set element per iteration
            elementVar->setElementAt(L"0", make_shared<Atom>(elem.first));
            elementVar->setElementAt(L"1", elem.second);

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

    void Engine::evaluateForLoop()
    {
        shared_ptr<Context> loopStack = make_shared<Context>();
        loopStack->setParent(getContext());
        // push function data onto stack
        stack.push_back(loopStack);

        wchar_t symbol;
        if ((symbol = readChar()) != L'(') {
            throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
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
            throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
        }

        // For loop
        int conditionPos = pos;
        int postStatementPos = -1;
        int loopBodyPos = -1;

        do {
            evaluateStatement();
            if ((symbol = readChar()) != L';') {
                throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
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

    void Engine::evaluateBlockOrStatement(bool stopOnBreak)
    {
        wchar_t symbol;
        if ((symbol = readChar()) != L'{') {
            // evaluate 1 statement
            unreadChar();
            evaluateStatement();
            if ((symbol = readChar()) != L';') {
                throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
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
                        throw runtime_error("Unexpected token '" + Tools::wideStrToStr(statementOp) + "'.");
                    break;
                }
            }
        }
    }

    void Engine::evaluateIfStructure()
    {
        shared_ptr<Atom> lastIfResult = make_shared<Atom>(nullptr);
        wchar_t symbol;
        if ((symbol = readChar()) != L'(') {
            throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'." );
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
                            throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
                        }
                        fastForward({L')'}, L'(');
                        skipBlockOrStatement();
                    } else {
                        if ((symbol = readChar()) != L'(') {
                            throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
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
                        throw runtime_error("Only 1 else statement can go after if.");
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

    void Engine::parseVariable(bool isConst) 
    {
        // Backup pos
        int prevPos = pos;

        wchar_t symbol = readChar();
        wstring varName;
        if (!parseCharacterSequence(symbol, varName)) {
            throw runtime_error("Failed to parse variable name.");
        }

        if (getContext()->hasOwnVar(varName)) {
            throw runtime_error("Variable '" + Tools::wideStrToStr(varName) + "' already defined.");
        }

        if (Tools::inVector<wstring>(reservedKeywords,varName)) {
            throw runtime_error("'" + Tools::wideStrToStr(varName) + "' is reserved keyword.");
        }

        auto newVar = make_shared<Atom>(nullptr);
        
        if (isConst) {
            getContext()->setConst(varName, newVar);
        } else {
            getContext()->setVar(varName, newVar);
        }

        pos = prevPos;

        evaluateStatement();

        if ((symbol = readChar()) == L',') {
            // recursively declare all variables
            parseVariable(isConst);
        } else {
            unreadChar();
        }
    }

    void Engine::parseFunction()
    {
        wchar_t symbol = readChar();
        wstring functionName;
        if (!parseCharacterSequence(symbol, functionName)) {
            throw runtime_error("Failed to parse function name.");
        }

        if (coreResolver.hasFunction(functionName)) {
            throw runtime_error("Function '" + Tools::wideStrToStr(functionName) + "' is core function.");
        }

        if (getContext()->hasOwnFunction(functionName)) {
            throw runtime_error("Function '" + Tools::wideStrToStr(functionName) + "' already defined.");
        }

        if (Tools::inVector<wstring>(reservedKeywords,functionName)) {
            throw runtime_error("'" + Tools::wideStrToStr(functionName) + "' is reserved keyword.");
        }

        if ((symbol = readChar()) != L'(') {
            throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
        }

        map<int, tuple<wstring, shared_ptr<Atom>, bool>> parameters;
        bool hasOptional = false;
        int paramIndex = 0;
        do {
            // function without parameters
            if ((symbol = readChar()) == L')') {
                break;
            }

            bool isReference = false;
            if (symbol == L'&') {
                isReference = true;
                symbol = readChar();
            }

            wstring argName;
            if (!parseCharacterSequence(symbol, argName)) {
                throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
            }

            for (auto const & parameter : parameters) {
                if (get<0>(parameter.second) == argName) {
                    throw runtime_error("Parameter with name '" 
                    + Tools::wideStrToStr(argName) 
                    + "' already exists.");
                }
            }

            if ((symbol = readChar()) == L'=') {
                // initializer for optional parameter
                if (isReference) {
                    throw runtime_error("Reference parameter cannot have default initializer.");
                }
                auto initializer = evaluateBoolStatement();
                parameters[paramIndex] = {argName, initializer, false};
                hasOptional = true;
            } else {
                // required parameter
                unreadChar();
                if (hasOptional) {
                    throw runtime_error("Required parameters cannot go after optional ones.");
                }
                parameters[paramIndex] = {argName, nullptr, isReference};
            }

            paramIndex++;
        } while ((symbol = readChar()) == L',');

        if (symbol != L')') {
            throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
        }

        getContext()->setFunction(functionName, pos, parameters);

        skipBlockOrStatement();
    }

    void Engine::evaluateStatement()
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
                throw runtime_error("Unexpected token '" + Tools::wideStrToStr(symbol) + "'.");
            }
        }

        // Empty statement
        if (symbol == L';') {
            // Last result is set to emtpy atom
            lastResult->setAtom(Atom(nullptr));
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

            // LOOP 
            if (keyWord == statementFor) {
                evaluateForLoop();
                if (!isReturn) {
                    dynamicSrc.push_back(L';');
                }
                return;
            }
            // END OF LOOP 

            // unread keyword
            unreadChar(keyWord.size());
        } else {
            unreadChar();
        }

        lastResult = evaluateBoolStatement();
    }

    void Engine::evaluateStatements()
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
                    unreadChar();
                    return;
            }
        }
    }

    shared_ptr<Atom> Engine::evaluate()
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
                        // Token has not been processed by any of top level parsers
                        throw runtime_error(
                            "Unexpected token '" 
                            + Tools::wideStrToStr(separator) 
                            + "'."
                        );
                    break;
                }
            }
        } catch(const exception & e) {
            throwError(e.what());
        }
        return lastResult;
    }

    shared_ptr<Atom> Engine::evaluateFile(wstring wfilename)
    {
        insertSource(wfilename);
        return evaluate();
    }

    shared_ptr<Atom> Engine::evaluateFile(string filename)
    {
        return evaluateFile(Tools::strToWideStr(filename));
    }

    shared_ptr<Atom> Engine::evaluateCode(wstring wcode)
    {
        insertSource(L"", wcode);
        return evaluate();
    }
    
    shared_ptr<Atom> Engine::evaluateCode(string code)
    {
        insertSource(L"", Tools::strToWideStr(code));
        return evaluate();
    }
}