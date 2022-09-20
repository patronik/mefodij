
#ifndef CAST_INT_JOINER_H
#define CAST_INT_JOINER_H

#include "../../../Joiner.h"

class CastIntJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
