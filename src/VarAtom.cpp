#include "../include/VarAtom.h"
namespace Mefodij {

    bool VarAtom::getIsConst()
    {
        return opts[0] == true;
    }

    bool VarAtom::getIsAssigned()
    {
        return opts[1] == true;
    }

    void VarAtom::setIsConst()
    {
        opts[0] = true;
    }

    void VarAtom::setIsAssigned()
    {
        opts[1] = true;
    }
}
