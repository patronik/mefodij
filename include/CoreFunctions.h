#ifndef CORE_FUNCTIONS_H
#define CORE_FUNCTIONS_H

#include "Atom.h"

using namespace std;

class CoreFunctions {
    map<wstring, pair<int, map<void (CoreFunctions::*)(), pair<wstring, shared_ptr<Atom>>>>> mapping;
    public:
    CoreFunctions(): mapping{} {};
};

#endif