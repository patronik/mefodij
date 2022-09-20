
#ifndef INT_ARRAY_JOINER_H
#define INT_ARRAY_JOINER_H

#include "../../../Joiner.h"

class IntArrayJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
