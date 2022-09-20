
#ifndef NULL_INT_JOINER_H
#define NULL_INT_JOINER_H

#include "../../../Joiner.h"

class NullIntJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
