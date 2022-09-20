
#ifndef CAST_DOUBLE_JOINER_H
#define CAST_DOUBLE_JOINER_H

#include "../../../Joiner.h"

class CastDoubleJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
