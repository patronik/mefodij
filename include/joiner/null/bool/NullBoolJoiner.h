
#ifndef NULL_BOOL_JOINER_H
#define NULL_BOOL_JOINER_H

#include "../../../Joiner.h"

class NullBoolJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
