#ifndef OBJECTDOUBLEJOINER_H
#define OBJECTDOUBLEJOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class ObjectDoubleJoiner: public Joiner 
{
 
 public:
 ObjectDoubleJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
