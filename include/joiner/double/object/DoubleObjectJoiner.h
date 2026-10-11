#ifndef DOUBLEOBJECTJOINER_H
#define DOUBLEOBJECTJOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class DoubleObjectJoiner: public Joiner 
{
 
 public:
 DoubleObjectJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
