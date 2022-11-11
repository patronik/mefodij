#ifndef VAR_ATOM_H
#define VAR_ATOM_H

#include <stdexcept>
#include <bitset>
#include "./Atom/Keyword.h"
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
    wstring varKey;

    public:
    // Getters
    bool getIsConst();
    bool getIsAssigned();
    wstring getVarKey();

    // Setters
    void setIsConst();
    void setIsAssigned();
    void setVarKey(wstring key);
  };

}

#endif