#ifndef OBJECTOBJECTJOINER_H
#define OBJECTOBJECTJOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class ObjectObjectJoiner: public Joiner 
{
 
 public:
 ObjectObjectJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
