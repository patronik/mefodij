#ifndef ATOM_PARSER_H
#define ATOM_PARSER_H

#include "CoreResolver.h"
#include "Atom.h"
#include "Parser.h"

namespace Mefodij {

    class AtomParser : public Parser
    {
        protected:
        // Return flag
        bool isReturn = false;

        // Breaks loop execution
        bool isBreak = false;

        // Result of last executed statement
        shared_ptr<Atom> lastResult{};

        // Stack
        vector<shared_ptr<Context>> stack{};

        CoreResolver coreResolver;

        /** VIRTUAL PART START */
        // helper functions
        virtual shared_ptr<Context> prepareCallStack(map<int, tuple<wstring, shared_ptr<Atom>, bool>> params) = 0;
        
        // state
        virtual tuple<int, wstring, wstring, bool, bool, shared_ptr<Atom>> getState() = 0;
        virtual void setState(const tuple<int, wstring, wstring, bool, bool, shared_ptr<Atom>> & state) = 0;

        // Get execution context
        virtual shared_ptr<Context> getContext() = 0;
        
        // One or more atoms connected with not bool operators (math)
        virtual shared_ptr<Atom> evaluateBoolExpression() = 0; 
        // one or more bool expressions conntected with bool operator
        virtual shared_ptr<Atom> evaluateBoolStatement() = 0; 
        virtual void evaluateBlockOrStatement(bool stopOnBreak = false) = 0;

        // Resolvers
        virtual void resolveCoreFunctionCall(wstring functionName, shared_ptr<Atom> & atom) = 0;
        virtual void resolveAtomAssignment(shared_ptr<Atom> & atom) = 0;
        virtual void resolveAtomAccess(shared_ptr<Atom> & atom) = 0;
        /** VIRTUAL PART END */

        // Atom parsers
        bool parseParentheticalAtom(wchar_t symbol, shared_ptr<Atom> & atom);
        bool parseBinNumberLiteralAtom(shared_ptr<Atom> & atom);
        bool parseHexNumberLiteralAtom(shared_ptr<Atom> & atom);
        bool parseNumberLiteralAtom(wchar_t symbol, shared_ptr<Atom> & atom);
        bool parseArrayLiteralAtom(wchar_t symbol, shared_ptr<Atom> & atom);
        bool parseDoubleQuotedStringAtom(wchar_t symbol, shared_ptr<Atom> & atom);
        bool parseSingleQuotedStringAtom(wchar_t symbol, shared_ptr<Atom> & atom);
        bool parseAlphabeticalAtom(wchar_t symbol, shared_ptr<Atom> & atom);
        bool parseCharacterConstAtom(wstring varName, shared_ptr<Atom> & atom);
        bool parseFunctionCallAtom(wstring varName, shared_ptr<Atom> & atom);

        // One atom
        shared_ptr<Atom> parseAtom();

        public:
        AtomParser();
        virtual ~AtomParser() {}
    };

}

#endif