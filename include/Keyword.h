#ifndef MEFODIJ_KEYWORD_H
#define MEFODIJ_KEYWORD_H

#include <string>
#include <vector>

using namespace std;
namespace Mefodij {
  class Keyword
  {
     public:
     static const wstring typeInt;
     static const wstring typeDouble;
     static const wstring typeString;
     static const wstring typeArray;
     static const wstring typeBool;
     static const wstring typeNull;

     static const vector<wstring> getTypes();

     static const wstring storageVar;
     static const wstring storageTmp;

     static const wstring castInt;
     static const wstring castDouble;
     static const wstring castString;
     static const wstring castArray;
     static const wstring castBool;

     static const wstring True;
     static const wstring False;
     static const wstring Null;

     static const wstring Length;
     static const wstring Size;
     static const wstring First;
     static const wstring Second;
     static const wstring Type;
     static const wstring Address;

    class Function {
      public:
      static const wstring inArray;
      static const wstring sortArray;  
      class Parameters {
         public:
         static const wstring elem;
         static const wstring array;
         static const wstring direction;
      };
    };
  };
}

#endif