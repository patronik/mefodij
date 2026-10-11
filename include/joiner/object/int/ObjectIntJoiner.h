#ifndef OBJECTINTJOINER_H
#define OBJECTINTJOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class ObjectIntJoiner: public Joiner 
{
 
 public:
 ObjectIntJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
