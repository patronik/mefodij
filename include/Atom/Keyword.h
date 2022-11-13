#ifndef MEFODIJ_KEYWORD_H
#define MEFODIJ_KEYWORD_H

#include <string>

using namespace std;
namespace Mefodij {
  namespace Keyword
  {
     extern const wstring typeInt;
     extern const wstring typeDouble;
     extern const wstring typeString;
     extern const wstring typeArray;
     extern const wstring typeBool;
     extern const wstring typeNull;

     extern const wstring storageVar;
     extern const wstring storageTmp;

     extern const wstring castInt;
     extern const wstring castDouble;
     extern const wstring castString;
     extern const wstring castArray;
     extern const wstring castBool;

     extern const wstring True;
     extern const wstring False;
     extern const wstring Null;

     extern const wstring Length;
     extern const wstring Size;
     extern const wstring First;
     extern const wstring Second;
     extern const wstring Type;
     extern const wstring Address;

    namespace Function {
       extern const wstring inArray;  
      namespace Parameters {
         extern const wstring elem;
         extern const wstring array;
      }
    }
  }
}

#endif