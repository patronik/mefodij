#ifndef VAR_ATOM_H
#define VAR_ATOM_H

#include <bitset>

namespace Mefodij {

  using namespace std;

  class VarAtom
  {
    protected:
    // variable state
    bitset<8> opts{0};

    public:
    // Getters
    bool getIsConst();
    bool getIsAssigned();

    // Setters
    void setIsConst();
    void setIsAssigned();
  };

}

#endif