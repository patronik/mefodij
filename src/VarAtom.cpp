#include "../include/VarAtom.h"
#include "../include/Keyword.h"
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

    void VarAtom::setIsReference()
    {
        opts[2] = true;
    }

    bool VarAtom::getIsReference()
    {
        return opts[2] == true;
    }

    void VarAtom::setIsArrayElem()
    {
        opts[3] = true;
    }

    bool VarAtom::getIsArrayElem()
    {
        return opts[3] == true;
    }

    wstring VarAtom::getKey()
    {
        return key;
    }

    void VarAtom::setKey(wstring val)
    {
        key = val;
    }
}
