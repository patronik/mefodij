
#ifndef ARRAY_STRING_JOINER_H
#define ARRAY_STRING_JOINER_H

#include "../../../Joiner.h"

class ArrayStringJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
