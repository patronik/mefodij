#ifndef VAR_ATOM_H
#define VAR_ATOM_H

#include <stdexcept>
#include <bitset>
#include "./Keyword.h"
namespace Mefodij {

  using namespace std;

  class VarAtom
  {
    protected:
    // variable state
    bitset<8> opts{0};

    // Value type
    wstring storageType = Keyword::storageTmp;

    // Variable storage key
    wstring key = L"";

    public:
    // Getters
    bool getIsConst();
    bool getIsAssigned();
    bool getIsReference();
    bool getIsArrayElem();
    wstring getStorageType();
    wstring getKey();

    // Setters
    void setIsConst();
    void setIsAssigned();
    void setIsReference();
    void setIsArrayElem();
    void setStorageType(wstring sT);
    void setKey(wstring key);
  };

}

#endif