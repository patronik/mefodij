
#ifndef CAST_ARRAY_JOINER_H
#define CAST_ARRAY_JOINER_H

#include "../../../Joiner.h"

class CastArrayJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
