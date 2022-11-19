#ifndef ATOM_H
#define ATOM_H

#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <map>

#include "VarAtom.h"
#include "tools.h"

namespace Mefodij {

  using namespace std;

  class Atom : public VarAtom
  {
      // DYNAMIC ATOM STATE START
      // atom type
      wstring type = L"null";

      // supported values
      long intVal = 0; // int

      // float point number
      double doubleVal = 0.00; 

      // string
      wstring stringVal = L"";
      // postion of a character in string
      int charIndex  = -1; 

      // boolean value
      bool boolVal = false; 

      // next not used integer key in array
      int arrayNextIndex = 0; 

      // array of atoms (values)
      map<wstring, shared_ptr<Atom>, Tools::arrayCmp> arrayVal; 

      // string representing catst type
      wstring castVal = L""; 

      // Reference to variable
      shared_ptr<Atom> varRef = nullptr;
      // DYNAMIC ATOM STATE END

      // Members
      map<wstring, map<wstring, void (Atom::*)()>> members{};

      // Member resolvers
      void resolveType();
      void resolveAddress();
      void resolveStringSize();
      void resolveArraySize();
      void resolveArrayFirst();
      void resolveArraySecond();

      void initMembers();
      
      void clearVal();
  public:
    Atom(void * nullPtr);
    Atom(long val);
    Atom(double val);
    Atom(wstring val);
    Atom(map<wstring, shared_ptr<Atom>, Tools::arrayCmp> val);
    Atom(bool val);

    // Getters
    long getInt();
    double getDouble();
    wstring getString();
    map<wstring, shared_ptr<Atom>, Tools::arrayCmp> getArray();
    bool getBool();
    int getCharIndex();
    int getArrayNextIndex();
    shared_ptr<Atom> getVarRef();
    wstring getType();

    // Setters
    void setVarRef(shared_ptr<Atom> atom);
    void setArrayNextIndex(const int index);
    void setCharIndex(const int index);
    void setInt(long val);
    void setDouble(double val);
    void setString(wstring val);
    void setStringChar(wchar_t val, int charIndex);
    void setArray(map<wstring, shared_ptr<Atom>, Tools::arrayCmp> val);
    void setBool(bool val);
    void setNull();
    void setAtom(const Atom & src);

    // Array related
    bool issetAt(wstring key);
    shared_ptr<Atom> elementAt(wstring key);
    void setElementAt(wstring key, shared_ptr<Atom> val);

    // Convertors
    bool toBool();
    wstring toString();

    // Operators supported by atom
    void preOperator(wstring op);
    void postOperator(wstring op);
    void unaryOperator(wstring op);

    // Convert atom from one type to another
    void cast(wstring typeTo);

    // Member names
    static vector<wstring> getMemberNames();
    // Member resolver
    void resolveMember(wstring name);
  };

}

#endif