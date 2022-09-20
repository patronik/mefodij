
#ifndef DOUBLE_NULL_JOINER_H
#define DOUBLE_NULL_JOINER_H

#include "../../../Joiner.h"

class DoubleNullJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
