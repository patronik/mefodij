#include "../include/FunctionContext.h"

void FunctionContext::set(wstring key, int pos, map<int, pair<wstring, shared_ptr<Atom>>> params) 
{
    storage.insert({key, {pos, params}});
}

bool FunctionContext::has(wstring key) {
    return storage.count(key) != 0;
}

pair<int, map<int, pair<wstring, shared_ptr<Atom>>>> & FunctionContext::get(wstring key) 
{
    return storage.at(key);
}