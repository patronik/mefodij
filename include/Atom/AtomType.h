#ifndef ATOM_TYPE_H
#define ATOM_TYPE_H

#include <string>

using namespace std;

class AtomType
{
  public:
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

  const static wstring keywordTrue;
  const static wstring keywordFalse;
  const static wstring keywordNull;
};

#endif