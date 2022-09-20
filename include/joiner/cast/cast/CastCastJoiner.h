
#ifndef CAST_CAST_JOINER_H
#define CAST_CAST_JOINER_H

#include "../../../Joiner.h"

class CastCastJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
