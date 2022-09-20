
#ifndef INT_CAST_JOINER_H
#define INT_CAST_JOINER_H

#include "../../../Joiner.h"

class IntCastJoiner : public Joiner 
{
 
 public:
 IntCastJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
