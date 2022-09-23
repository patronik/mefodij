
#ifndef STRING_ARRAY_JOINER_H
#define STRING_ARRAY_JOINER_H

#include "../../../Joiner.h"

class StringArrayJoiner: public Joiner 
{
 
 public:
 StringArrayJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
