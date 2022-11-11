#include "../include/VarAtom.h"
#include "../include/Atom/Keyword.h"
namespace Mefodij {

    bool VarAtom::getIsConst()
    {
        if (storageType != Keyword::storageVar) {
            throw runtime_error("An attempt to get variable option on non variable.");
        }
        return opts[0] == true;
    }

    bool VarAtom::getIsAssigned()
    {
        if (storageType != Keyword::storageVar) {
            throw runtime_error("An attempt to get variable option on non variable.");
        }
        return opts[1] == true;
    }

    void VarAtom::setIsConst()
    {
        if (storageType != Keyword::storageVar) {
            throw runtime_error("An attempt to set variable option on non variable.");
        }
        opts[0] = true;
    }

    void VarAtom::setIsAssigned()
    {
        if (storageType != Keyword::storageVar) {
            throw runtime_error("An attempt to set variable option on non variable.");
        }
        opts[1] = true;
    }

    void VarAtom::setIsReference()
    {
        if (storageType != Keyword::storageVar) {
            throw runtime_error("An attempt to make reference to variable on non variable.");
        }
        opts[2] = true;
    }

    bool VarAtom::getIsReference()
    {
        if (storageType != Keyword::storageVar) {
            throw runtime_error("An attempt to get variable option on non variable.");
        }
        return opts[2] == true;
    }

    wstring VarAtom::getKey()
    {
        if (storageType != Keyword::storageVar) {
            throw runtime_error("An attempt to get variable key on non variable.");
        }
        return key;
    }

    void VarAtom::setKey(wstring val)
    {
        if (storageType != Keyword::storageVar) {
            throw runtime_error("An attempt to set variable key on non variable.");
        }
        key = val;
    }
}
