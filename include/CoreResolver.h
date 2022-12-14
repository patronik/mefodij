#ifndef CORE_FUNCTION_RESOLVER_H
#define CORE_FUNCTION_RESOLVER_H

#include "Atom.h"
#include "Context.h"

namespace Mefodij {

    using namespace std;

    class CoreResolver {
        typedef map<int, tuple<wstring, shared_ptr<Atom>, bool>> methodParams;
        typedef void (CoreResolver::* methodPtr)(shared_ptr<Context> &, shared_ptr<Atom> &);

        map<wstring, pair<methodPtr, methodParams>> storage;

        methodPtr getPointer(wstring name);

        struct ArrayGTCmp
        {
            inline bool operator() (
                pair<wstring, shared_ptr<Atom>> const & a1, 
                pair<wstring, shared_ptr<Atom>> const & a2)
            {
                return a1.second->toString() < a2.second->toString();
            }
        };

        struct ArrayLTCmp
        {
            inline bool operator() (
                pair<wstring, shared_ptr<Atom>> const & a1, 
                pair<wstring, shared_ptr<Atom>> const & a2)
            {
                return a1.second->toString() > a2.second->toString();
            }
        };

        // core functions
        void inArray(shared_ptr<Context> & stack, shared_ptr<Atom> & result);
        void sortArray(shared_ptr<Context> & stack, shared_ptr<Atom> & result);

        public:
        CoreResolver();
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

}

#endif