
#ifndef NULL_CAST_JOINER_H
#define NULL_CAST_JOINER_H

#include "../../../Joiner.h"

class NullCastJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
