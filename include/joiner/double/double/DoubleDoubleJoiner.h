
#ifndef DOUBLE_DOUBLE_JOINER_H
#define DOUBLE_DOUBLE_JOINER_H

#include "../../../Joiner.h"

class DoubleDoubleJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
