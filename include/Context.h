#ifndef CONTEXT_H
#define CONTEXT_H

#include "tools.h"
#include "Atom.h"
#include "FunctionContext.h"

namespace Mefodij {

    using namespace std;

    class Context {
        shared_ptr<Context> parentContext = nullptr;
        map<wstring, shared_ptr<Atom>> storage{};
        // Functions
        FunctionContext functions{};

    public:
        // Variables
        void setVar(wstring key, shared_ptr<Atom> var);
        void setConst(wstring key, shared_ptr<Atom> var);
        bool hasVar(wstring key);
        bool hasOwnVar(wstring key);
        shared_ptr<Atom> getVar(wstring key);

        Context * getVarContext(wstring key);
        
        // Var to Var alias
        void setVarToVarAlias(wstring keyFrom, wstring keyTo);

        // Functions
        void setFunction(wstring key, int pos, map<int, tuple<wstring, shared_ptr<Atom>, bool>> params); 
        bool hasFunction(wstring key);
        bool hasOwnFunction(wstring key);
        pair<int, map<int, tuple<wstring, shared_ptr<Atom>, bool>>> & getFunction(wstring key);
        // Parent context
        void setParent(shared_ptr<Context> parent);
        Context();
    };

}

#endif