
#ifndef ARRAY_INT_JOINER_H
#define ARRAY_INT_JOINER_H

#include "../../../Joiner.h"

class ArrayIntJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
