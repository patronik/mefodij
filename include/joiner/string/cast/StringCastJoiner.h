
#ifndef STRING_CAST_JOINER_H
#define STRING_CAST_JOINER_H

#include "../../../Joiner.h"

class StringCastJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
