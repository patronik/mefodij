
#ifndef DOUBLE_CAST_JOINER_H
#define DOUBLE_CAST_JOINER_H

#include "../../../Joiner.h"

class DoubleCastJoiner : public Joiner 
{
 
 public:
 DoubleCastJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
