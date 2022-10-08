#include "../include/Functions.h"

void Functions::set(wstring key, int pos, map<int, pair<wstring, shared_ptr<Atom>>> params) 
{
    storage.insert({key, {pos, params}});
}

bool Functions::has(wstring key) {
    return storage.count(key) != 0;
}

pair<int, map<int, pair<wstring, shared_ptr<Atom>>>> & Functions::get(wstring key) 
{
    return storage.at(key);
}