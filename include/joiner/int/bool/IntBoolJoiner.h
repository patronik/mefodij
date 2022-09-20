
#ifndef INT_BOOL_JOINER_H
#define INT_BOOL_JOINER_H

#include "../../../Joiner.h"

class IntBoolJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
