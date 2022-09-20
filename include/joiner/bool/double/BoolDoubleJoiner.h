
#ifndef BOOL_DOUBLE_JOINER_H
#define BOOL_DOUBLE_JOINER_H

#include "../../../Joiner.h"

class BoolDoubleJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
