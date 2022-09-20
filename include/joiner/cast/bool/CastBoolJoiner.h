
#ifndef CAST_BOOL_JOINER_H
#define CAST_BOOL_JOINER_H

#include "../../../Joiner.h"

class CastBoolJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
