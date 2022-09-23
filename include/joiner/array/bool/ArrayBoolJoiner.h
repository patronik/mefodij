
#ifndef ARRAY_BOOL_JOINER_H
#define ARRAY_BOOL_JOINER_H

#include "../../../Joiner.h"

class ArrayBoolJoiner: public Joiner 
{
 
 public:
 ArrayBoolJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
