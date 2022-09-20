
#ifndef ARRAY_DOUBLE_JOINER_H
#define ARRAY_DOUBLE_JOINER_H

#include "../../../Joiner.h"

class ArrayDoubleJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
