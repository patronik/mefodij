#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <cwctype>
#include <map>
#include <wchar.h>

#include "Atom.h"
#include "AtomParser.h"
#include "Context.h"

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

  class Engine : public AtomParser
  {
      // Global context
      shared_ptr<Context> context = nullptr;

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

      virtual shared_ptr<Context> getContext() override;

      // one or more atoms connected with high priority math operator 
      shared_ptr<Atom> evaluateMathExpression(); 
      // one ore more math expression connected with low level priority operator 
      virtual shared_ptr<Atom> evaluateBoolExpression() override; 
      // one or more bool expressions conntected with bool operator
      virtual shared_ptr<Atom> evaluateBoolStatement() override; 

      // helper functions
      virtual shared_ptr<Context> prepareCallStack(map<int, tuple<wstring, shared_ptr<Atom>, bool>> params) override;

      // Atom resolvers
      void resolveStringAccess(shared_ptr<Atom> & atom);
      void resolveArrayAccess(shared_ptr<Atom> & atom);
      void resolveMemberAccess(shared_ptr<Atom> & atom);
      virtual void resolveCoreFunctionCall(wstring functionName, shared_ptr<Atom> & atom) override;
      virtual void resolveAtomAssignment(shared_ptr<Atom> & atom) override;
      virtual void resolveAtomAccess(shared_ptr<Atom> & atom) override;

      // Parsers for function and variable declaration
      void parseVariable(bool isConst = false);
      void parseFunction();
      
      void evaluateWhileLoop(int firstStmtPos);
      void evaluateRangeLoop(int firstStmtPos);
      void evaluateForLoop();
      void evaluateIfStructure();
      virtual void evaluateBlockOrStatement(bool stopOnBreak = false) override;
      void evaluateStatement();
      void evaluateStatements();
      shared_ptr<Atom> evaluate();

      tuple<int, wstring, wstring, bool, bool, shared_ptr<Atom>> getState() override;
      virtual void setState(const tuple<int, wstring, wstring, bool, bool, shared_ptr<Atom>> & state) override;

      void throwError(const string message);
  public:
    Engine();
    virtual ~Engine() {}
    shared_ptr<Atom> evaluateFile(string filename);
    shared_ptr<Atom> evaluateFile(wstring wfilename);
    shared_ptr<Atom> evaluateCode(string code);
    shared_ptr<Atom> evaluateCode(wstring wcode);
  };

}

#endif