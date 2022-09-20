
#ifndef NULL_ARRAY_JOINER_H
#define NULL_ARRAY_JOINER_H

#include "../../../Joiner.h"

class NullArrayJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
