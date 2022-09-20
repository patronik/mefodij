
#ifndef INT_STRING_JOINER_H
#define INT_STRING_JOINER_H

#include "../../../Joiner.h"

class IntStringJoiner : public Joiner 
{
 
 public:
 IntStringJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
