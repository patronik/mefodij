#ifndef FUNCTION_CONTEXT_H
#define FUNCTION_CONTEXT_H

#include "Atom.h"

namespace Mefodij {

    using namespace std;

    class FunctionContext {
        map<wstring, pair<int, map<int, tuple<wstring, shared_ptr<Atom>, bool>>>> storage;
        public:
        void set(wstring key, int pos, map<int, tuple<wstring, shared_ptr<Atom>, bool>> params); 
        bool has(wstring key);
        pair<int, map<int, tuple<wstring, shared_ptr<Atom>, bool>>> & get(wstring key);
        FunctionContext(): storage{} {};
    };

}

#endif