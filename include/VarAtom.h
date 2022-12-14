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

    // Variable storage key
    wstring key = L"";

    public:
    // Getters
    bool getIsConst();
    bool getIsAssigned();
    bool getIsReference();
    bool getIsArrayElem();
    wstring getKey();

    // Setters
    void setIsConst();
    void setIsAssigned();
    void setIsReference();
    void setIsArrayElem();
    void setKey(wstring key);
  };

}

#endif