#ifndef CORE_FUNCTION_RESOLVER_H
#define CORE_FUNCTION_RESOLVER_H

#include "Atom.h"
#include "Context.h"

using namespace std;

class CoreFunctionResolver {
    typedef map<int, pair<wstring, shared_ptr<Atom>>> methodParams;
    typedef void (CoreFunctionResolver::* methodPtr)(shared_ptr<Context> &, shared_ptr<Atom> &);

    map<wstring, pair<methodPtr, methodParams>> storage;

    methodPtr getPointer(wstring name);

    // core functions
    void inArray(shared_ptr<Context> & stack, shared_ptr<Atom> & result);

    public:
    CoreFunctionResolver();
    methodParams & getParams(wstring name);

    bool hasFunction(wstring name);

    void setFunction(
        wstring name, 
        methodPtr method,
        methodParams params
    ); 

    void resolveCall(
        wstring name, 
        shared_ptr<Context> & stack, 
        shared_ptr<Atom> & result
    );
};

#endif