#ifndef OBJECTARRAYJOINER_H
#define OBJECTARRAYJOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class ObjectArrayJoiner: public Joiner 
{
 
 public:
 ObjectArrayJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
