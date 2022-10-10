#ifndef ATOM_H
#define ATOM_H

#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <map>

using namespace std;

class Atom
{
    wstring type = L"null";
    int intVal = 0;
    double doubleVal = 0.00;
    wstring stringVal = L"";
    bool boolVal = false;
    wstring castVal = L"";
    map<wstring, shared_ptr<Atom>> arrayVal;
    
    int stringVarCharIndex  = -1;
    shared_ptr<Atom> varRef = nullptr;
    
    void clearVal();

public:
  Atom();
  Atom(int val);
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

  static vector<wstring> castTypes;

  void setVar(shared_ptr<Atom> atom);
  shared_ptr<Atom> getVar();
  int getCharIndex();
  void setCharIndex(const int index);

  wstring getType();

  void setInt(int val);
  void setDouble(double val);
  void setString(wstring val);
  void setStringChar(wchar_t val, int charIndex);
  void setArray(map<wstring, shared_ptr<Atom>> val);
  void setBool(bool val);
  void setNull();
  void setCast(wstring val);
  void setAtom(const shared_ptr<Atom> & src);

  int getInt();
  double getDouble();
  wstring getString();
  map<wstring, shared_ptr<Atom>> getArray();
  bool getBool();
  wstring getCast();

  bool issetAt(wstring key);
  shared_ptr<Atom> elementAt(wstring key);
  void createAt(wstring key, shared_ptr<Atom> val);

  bool toBool();
  wstring toString();

  void preOperator(wstring op);
  void postOperator(wstring op);
  void unaryOperator(wstring op);
  void cast(wstring typeTo);
};

#endif