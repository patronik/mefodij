#ifndef CONTEXT_H
#define CONTEXT_H

#include "tools.h"
#include "Atom.h"
#include "FunctionContext.h"

using namespace std;

class Context {
    shared_ptr<Context> parentContext = nullptr;
    map<wstring, shared_ptr<Atom>> storage{};
    // Functions
    FunctionContext functions{};

public:
    // Variables
    void setVar(wstring key, shared_ptr<Atom> var);
    bool hasVar(wstring key);
    bool hasOwnVar(wstring key);
    shared_ptr<Atom> getVar(wstring key);
    // Functions
    void setFunction(wstring key, int pos, map<int, pair<wstring, shared_ptr<Atom>>> params); 
    bool hasFunction(wstring key);
    bool hasOwnFunction(wstring key);
    pair<int, map<int, pair<wstring, shared_ptr<Atom>>>> & getFunction(wstring key);
    // Parent context
    void setParent(shared_ptr<Context> parent);
    Context();
};

#endif