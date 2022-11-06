
#ifndef INT_INT_JOINER_H
#define INT_INT_JOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class IntIntJoiner : public Joiner 
{
 
 public:
 IntIntJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
