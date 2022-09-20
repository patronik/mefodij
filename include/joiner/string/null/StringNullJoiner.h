
#ifndef STRING_NULL_JOINER_H
#define STRING_NULL_JOINER_H

#include "../../../Joiner.h"

class StringNullJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
