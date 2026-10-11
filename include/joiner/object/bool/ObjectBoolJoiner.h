#ifndef OBJECTBOOLJOINER_H
#define OBJECTBOOLJOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class ObjectBoolJoiner: public Joiner 
{
 
 public:
 ObjectBoolJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
