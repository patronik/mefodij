
#ifndef BOOL_CAST_JOINER_H
#define BOOL_CAST_JOINER_H

#include "../../../Joiner.h"

class BoolCastJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
