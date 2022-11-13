#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <cwctype>
#include <map>
#include <wchar.h>

#include "Parser.h"
#include "Atom.h"
#include "Context.h"
#include "CoreFunctionResolver.h"

#include "joiner/bool/bool/BoolBoolJoiner.h"
#include "joiner/bool/int/BoolIntJoiner.h"
#include "joiner/bool/null/BoolNullJoiner.h"
#include "joiner/bool/array/BoolArrayJoiner.h"
#include "joiner/bool/double/BoolDoubleJoiner.h"
#include "joiner/bool/string/BoolStringJoiner.h"
#include "joiner/int/bool/IntBoolJoiner.h"
#include "joiner/int/int/IntIntJoiner.h"
#include "joiner/int/null/IntNullJoiner.h"
#include "joiner/int/array/IntArrayJoiner.h"
#include "joiner/int/double/IntDoubleJoiner.h"
#include "joiner/int/string/IntStringJoiner.h"
#include "joiner/null/bool/NullBoolJoiner.h"
#include "joiner/null/int/NullIntJoiner.h"
#include "joiner/null/null/NullNullJoiner.h"
#include "joiner/null/array/NullArrayJoiner.h"
#include "joiner/null/double/NullDoubleJoiner.h"
#include "joiner/null/string/NullStringJoiner.h"
#include "joiner/array/bool/ArrayBoolJoiner.h"
#include "joiner/array/int/ArrayIntJoiner.h"
#include "joiner/array/null/ArrayNullJoiner.h"
#include "joiner/array/array/ArrayArrayJoiner.h"
#include "joiner/array/double/ArrayDoubleJoiner.h"
#include "joiner/array/string/ArrayStringJoiner.h"
#include "joiner/double/bool/DoubleBoolJoiner.h"
#include "joiner/double/int/DoubleIntJoiner.h"
#include "joiner/double/null/DoubleNullJoiner.h"
#include "joiner/double/array/DoubleArrayJoiner.h"
#include "joiner/double/double/DoubleDoubleJoiner.h"
#include "joiner/double/string/DoubleStringJoiner.h"
#include "joiner/string/bool/StringBoolJoiner.h"
#include "joiner/string/int/StringIntJoiner.h"
#include "joiner/string/null/StringNullJoiner.h"
#include "joiner/string/array/StringArrayJoiner.h"
#include "joiner/string/double/StringDoubleJoiner.h"
#include "joiner/string/string/StringStringJoiner.h"

namespace Mefodij {

  using namespace std;

  class Engine : public Parser
  {
      // Return flag
      bool isReturn = false;

      // Breaks loop execution
      bool isBreak = false;

      // Result of last executed statement
      shared_ptr<Atom> lastResult{};

      // Global context
      shared_ptr<Context> context = nullptr;

      // Stack
      vector<shared_ptr<Context>> stack{};

      CoreFunctionResolver coreFuncResolver;

      static unique_ptr<BoolBoolJoiner> boolBoolJoiner;
      static unique_ptr<BoolIntJoiner> boolIntJoiner;
      static unique_ptr<BoolNullJoiner> boolNullJoiner;
      static unique_ptr<BoolArrayJoiner> boolArrayJoiner;
      static unique_ptr<BoolDoubleJoiner> boolDoubleJoiner;
      static unique_ptr<BoolStringJoiner> boolStringJoiner;
      static unique_ptr<IntBoolJoiner> intBoolJoiner;
      static unique_ptr<IntIntJoiner> intIntJoiner;
      static unique_ptr<IntNullJoiner> intNullJoiner;
      static unique_ptr<IntArrayJoiner> intArrayJoiner;
      static unique_ptr<IntDoubleJoiner> intDoubleJoiner;
      static unique_ptr<IntStringJoiner> intStringJoiner;
      static unique_ptr<NullBoolJoiner> nullBoolJoiner;
      static unique_ptr<NullIntJoiner> nullIntJoiner;
      static unique_ptr<NullNullJoiner> nullNullJoiner;
      static unique_ptr<NullArrayJoiner> nullArrayJoiner;
      static unique_ptr<NullDoubleJoiner> nullDoubleJoiner;
      static unique_ptr<NullStringJoiner> nullStringJoiner;
      static unique_ptr<ArrayBoolJoiner> arrayBoolJoiner;
      static unique_ptr<ArrayIntJoiner> arrayIntJoiner;
      static unique_ptr<ArrayNullJoiner> arrayNullJoiner;
      static unique_ptr<ArrayArrayJoiner> arrayArrayJoiner;
      static unique_ptr<ArrayDoubleJoiner> arrayDoubleJoiner;
      static unique_ptr<ArrayStringJoiner> arrayStringJoiner;
      static unique_ptr<DoubleBoolJoiner> doubleBoolJoiner;
      static unique_ptr<DoubleIntJoiner> doubleIntJoiner;
      static unique_ptr<DoubleNullJoiner> doubleNullJoiner;
      static unique_ptr<DoubleArrayJoiner> doubleArrayJoiner;
      static unique_ptr<DoubleDoubleJoiner> doubleDoubleJoiner;
      static unique_ptr<DoubleStringJoiner> doubleStringJoiner;
      static unique_ptr<StringBoolJoiner> stringBoolJoiner;
      static unique_ptr<StringIntJoiner> stringIntJoiner;
      static unique_ptr<StringNullJoiner> stringNullJoiner;
      static unique_ptr<StringArrayJoiner> stringArrayJoiner;
      static unique_ptr<StringDoubleJoiner> stringDoubleJoiner;
      static unique_ptr<StringStringJoiner> stringStringJoiner;

      void joinAtoms(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);
      void assignToAtom(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

      shared_ptr<Context> getContext();

      // one atom
      shared_ptr<Atom> parseAtom();
      // one or more atoms connected with high priority math operator 
      shared_ptr<Atom> evaluateMathExpression(); 
      // one ore more math expression connected with low level priority operator 
      shared_ptr<Atom> evaluateBoolExpression(); 
      // one or more bool expressions conntected with bool operator
      shared_ptr<Atom> evaluateBoolStatement(); 

      // helper functions
      bool isType(wstring str);
      shared_ptr<Context> prepareCallStack(map<int, tuple<wstring, shared_ptr<Atom>, bool>> params);

      // Atoms parsers
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

      // Parsers for function and variable declaration
      void parseVariable(bool isConst = false);
      void parseFunction();
      
      // Atom resolving
      void resolveCoreFunctionCall(wstring functionName, shared_ptr<Atom> & atom);
      void resolveStringAccess(shared_ptr<Atom> & atom);
      void resolveArrayAccess(shared_ptr<Atom> & atom);
      void resolveMemberAccess(shared_ptr<Atom> & atom);
      void resolveAtomAssignment(shared_ptr<Atom> & atom);
      void resolveAtomAccess(shared_ptr<Atom> & atom);
      
      void evaluateWhileLoop(int firstStmtPos);
      void evaluateRangeLoop(int firstStmtPos);
      void evaluateForLoop();
      void evaluateIfStructure();
      void evaluateBlockOrStatement(bool stopOnBreak = false);
      void evaluateStatement();
      void evaluateStatements();
      shared_ptr<Atom> evaluate();

      tuple<int, wstring, wstring, bool, bool, shared_ptr<Atom>> getState();
      void setState(const tuple<int, wstring, wstring, bool, bool, shared_ptr<Atom>> & state);

      void throwError(const string message);
  public:
    Engine();
    shared_ptr<Atom> evaluateFile(string filename);
    shared_ptr<Atom> evaluateFile(wstring wfilename);
    shared_ptr<Atom> evaluateCode(string code);
    shared_ptr<Atom> evaluateCode(wstring wcode);
  };

}

#endif