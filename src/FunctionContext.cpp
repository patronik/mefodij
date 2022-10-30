#include "../include/FunctionContext.h"

namespace Mefody {

    void FunctionContext::set(wstring key, int pos, map<int, tuple<wstring, shared_ptr<Atom>, bool>> params) 
    {
        storage.insert({key, {pos, params}});
    }

    bool FunctionContext::has(wstring key) {
        return storage.count(key) != 0;
    }

    pair<int, map<int, tuple<wstring, shared_ptr<Atom>, bool>>> & FunctionContext::get(wstring key) 
    {
        return storage.at(key);
    }

}