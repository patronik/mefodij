
#ifndef ARRAY_ARRAY_JOINER_H
#define ARRAY_ARRAY_JOINER_H

#include "../../../Joiner.h"

class ArrayArrayJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
