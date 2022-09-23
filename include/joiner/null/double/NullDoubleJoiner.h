
#ifndef NULL_DOUBLE_JOINER_H
#define NULL_DOUBLE_JOINER_H

#include "../../../Joiner.h"

class NullDoubleJoiner: public Joiner 
{
 
 public:
 NullDoubleJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
