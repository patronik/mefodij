
#ifndef NULL_NULL_JOINER_H
#define NULL_NULL_JOINER_H

#include "../../../Joiner.h"

class NullNullJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
