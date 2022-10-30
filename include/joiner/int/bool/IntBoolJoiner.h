
#ifndef INT_BOOL_JOINER_H
#define INT_BOOL_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class IntBoolJoiner : public Joiner 
{
 
 public:
 IntBoolJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
