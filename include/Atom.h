#ifndef ATOM_H
#define ATOM_H

#include <bitset>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <map>

using namespace std;

class Atom
{
    // atom state
    bitset<sizeof(int)> options{0};

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
    map<wstring, shared_ptr<Atom>> arrayVal; 

    // string representing catst type
    wstring castVal = L""; 

    // Reference to variable
    shared_ptr<Atom> varRef = nullptr;

    // Members
    map<wstring, map<wstring, void (Atom::*)()>> members{};

    // Member resolvers
    void resolveStringSize();
    void resolveArraySize();
    void resolveArrayFirst();
    void resolveArraySecond();

    void initMembers();
    
    void clearVal();
public:
  Atom();
  Atom(long val);
  Atom(double val);
  Atom(wstring val);
  Atom(map<wstring, shared_ptr<Atom>> val);
  Atom(bool val);

  const static wstring typeInt;
  const static wstring typeDouble;
  const static wstring typeString;
  const static wstring typeArray;
  const static wstring typeBool;
  const static wstring typeNull;
  const static wstring typeCast;

  const static wstring castInt;
  const static wstring castDouble;
  const static wstring castString;
  const static wstring castArray;
  const static wstring castBool;
  const static wstring castNull;

  // Getters
  long getInt();
  double getDouble();
  wstring getString();
  map<wstring, shared_ptr<Atom>> getArray();
  bool getBool();
  wstring getCast();
  int getCharIndex();
  int getArrayNextIndex();
  shared_ptr<Atom> getVar();
  wstring getType();
  bool getIsConst();
  bool getIsAssigned();
  bool getIsCalculated();

  // Setters
  void setVar(shared_ptr<Atom> atom);
  void setArrayNextIndex(const int index);
  void setCharIndex(const int index);
  void setInt(long val);
  void setDouble(double val);
  void setString(wstring val);
  void setStringChar(wchar_t val, int charIndex);
  void setArray(map<wstring, shared_ptr<Atom>> val);
  void setBool(bool val);
  void setNull();
  void setCast(wstring val);
  void setAtom(const Atom & src);
  void setIsConst();
  void setIsAssigned();
  void setIsCalculated();

  // Array related
  bool issetAt(wstring key);
  shared_ptr<Atom> elementAt(wstring key);
  void createAt(wstring key, shared_ptr<Atom> val);

  // Convertors
  bool toBool();
  wstring toString();

  // Operators supported by atom
  void preOperator(wstring op);
  void postOperator(wstring op);
  void unaryOperator(wstring op);

  // Convert atom from one type to another
  void cast(wstring typeTo);

  // Member resolver
  void resolveMember(wstring name);
};

#endif