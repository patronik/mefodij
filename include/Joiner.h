#ifndef JOINER_H
#define JOINER_H

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <memory>

#include "Atom.h"

using namespace std;


class Joiner 
{
    protected:
    vector<wstring> operators;
    virtual void validate(wstring op);

    public:
    virtual void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right) = 0;
};

#endif