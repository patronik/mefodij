#ifndef FUNCTION_STORAGE_H
#define FUNCTION_STORAGE_H

#include "Atom.h"

using namespace std;

class FunctionStorage {
    map<wstring, pair<int, map<int, pair<wstring, shared_ptr<Atom>>>>> storage;
    public:
    void set(wstring key, int pos, map<int, pair<wstring, shared_ptr<Atom>>> params); 
    bool has(wstring key);
    pair<int, map<int, pair<wstring, shared_ptr<Atom>>>> & get(wstring key);
    FunctionStorage(): storage{} {};
};

#endif