
#ifndef ARRAY_NULL_JOINER_H
#define ARRAY_NULL_JOINER_H

#include "../../../Joiner.h"

class ArrayNullJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
