
#ifndef DOUBLE_BOOL_JOINER_H
#define DOUBLE_BOOL_JOINER_H

#include "../../../Joiner.h"

class DoubleBoolJoiner: public Joiner 
{
 
 public:
 DoubleBoolJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
