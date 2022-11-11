#include "../../include/Atom/Keyword.h"
namespace Mefodij {
  namespace Keyword
  {
    const wstring typeInt(L"int");
    const wstring typeDouble(L"double");
    const wstring typeString(L"string");
    const wstring typeArray(L"array");
    const wstring typeBool(L"bool");
    const wstring typeNull(L"null");
    const wstring typeCast(L"cast");

    const wstring storageVar(L"variable");
    const wstring storageTmp(L"temporary");

    const wstring castInt(L"ціле");
    const wstring castDouble(L"дійсне");
    const wstring castString(L"строка");
    const wstring castArray(L"масив");
    const wstring castBool(L"бул");

    const wstring True(L"так");
    const wstring False(L"ні");
    const wstring Null(L"нал");

    const wstring Length(L"довжина");
    const wstring Size(L"розмір");
    const wstring First(L"перший");
    const wstring Second(L"другий");

    namespace Function {
      const wstring inArray(L"вМасиві");;  
      namespace Parameters {
        const wstring elem(L"елемент");;
        const wstring array(L"масив");;
      }
    }
  }
}