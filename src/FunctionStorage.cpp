#include "../include/FunctionStorage.h"

void FunctionStorage::set(wstring key, int pos, map<int, pair<wstring, shared_ptr<Atom>>> params) 
{
    storage.insert({key, {pos, params}});
}

bool FunctionStorage::has(wstring key) {
    return storage.count(key) != 0;
}

pair<int, map<int, pair<wstring, shared_ptr<Atom>>>> & FunctionStorage::get(wstring key) 
{
    return storage.at(key);
}