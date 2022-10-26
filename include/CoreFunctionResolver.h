#ifndef CORE_FUNCTION_RESOLVER_H
#define CORE_FUNCTION_RESOLVER_H

#include "Atom.h"

using namespace std;

class CoreFunctionResolver {
    map<wstring, void (CoreFunctionResolver::*)(), map<int, pair<wstring, shared_ptr<Atom>>>> functions;
    public:
    bool has(wstring name);
    void set(
        wstring name, 
        void (CoreFunctionResolver::* method)(map<wstring, shared_ptr<Atom>>, shared_ptr<Atom> & ret), 
        map<int, pair<wstring, shared_ptr<Atom>>> params
    ); 
    void resolve(wstring name, map<int, pair<wstring, shared_ptr<Atom>>> params, shared_ptr<Atom> & ret);
    CoreFunctionResolver(): functions{} {};
};

#endif