#include "../include/Keyword.h"

namespace Mefodij {
  
  const wstring Keyword::typeInt(L"ціле");
  const wstring Keyword::typeDouble(L"дійсне");
  const wstring Keyword::typeString(L"строка");
  const wstring Keyword::typeArray(L"масив");
  const wstring Keyword::typeBool(L"бул");
  const wstring Keyword::typeNull(L"нал");

  const vector<wstring> Keyword::getTypes()
  {
    return {
      typeInt, typeDouble, typeString, typeArray, typeBool, typeNull
    };
  }

  const wstring Keyword::storageVar(L"змінна");
  const wstring Keyword::storageTmp(L"тмп");

  const wstring Keyword::True(L"так");
  const wstring Keyword::False(L"ні");
  const wstring Keyword::Null(L"нал");

  const wstring Keyword::Length(L"довжина");
  const wstring Keyword::Size(L"розмір");
  const wstring Keyword::First(L"перший");
  const wstring Keyword::Second(L"другий");

  const wstring Keyword::Type(L"тип");
  const wstring Keyword::Address(L"адрес");

  const wstring Keyword::Function::inArray(L"вМасиві");
  const wstring Keyword::Function::sortArray(L"сортувати");  
  const wstring Keyword::Function::Parameters::elem(L"елемент");
  const wstring Keyword::Function::Parameters::array(L"масив");
  const wstring Keyword::Function::Parameters::direction(L"порядок");


}