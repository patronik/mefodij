#ifndef ARRAYOBJECTJOINER_H
#define ARRAYOBJECTJOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class ArrayObjectJoiner: public Joiner 
{
 
 public:
 ArrayObjectJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
