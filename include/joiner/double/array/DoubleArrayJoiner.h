
#ifndef DOUBLE_ARRAY_JOINER_H
#define DOUBLE_ARRAY_JOINER_H

#include "../../../Joiner.h"

class DoubleArrayJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
