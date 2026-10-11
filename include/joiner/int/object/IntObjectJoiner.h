#ifndef INTOBJECTJOINER_H
#define INTOBJECTJOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class IntObjectJoiner: public Joiner 
{
 
 public:
 IntObjectJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
