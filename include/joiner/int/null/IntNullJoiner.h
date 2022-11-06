
#ifndef INT_NULL_JOINER_H
#define INT_NULL_JOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class IntNullJoiner : public Joiner 
{
 
 public:
 IntNullJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
