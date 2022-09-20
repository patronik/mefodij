
#ifndef ARRAY_CAST_JOINER_H
#define ARRAY_CAST_JOINER_H

#include "../../../Joiner.h"

class ArrayCastJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
