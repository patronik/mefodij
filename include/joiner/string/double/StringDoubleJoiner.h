
#ifndef STRING_DOUBLE_JOINER_H
#define STRING_DOUBLE_JOINER_H

#include "../../../Joiner.h"

class StringDoubleJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
