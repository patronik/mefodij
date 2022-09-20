
#ifndef CAST_NULL_JOINER_H
#define CAST_NULL_JOINER_H

#include "../../../Joiner.h"

class CastNullJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
