#ifndef BOOLOBJECTJOINER_H
#define BOOLOBJECTJOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class BoolObjectJoiner: public Joiner 
{
 
 public:
 BoolObjectJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
