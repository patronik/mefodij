#ifndef OBJECTNULLJOINER_H
#define OBJECTNULLJOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class ObjectNullJoiner: public Joiner 
{
 
 public:
 ObjectNullJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
