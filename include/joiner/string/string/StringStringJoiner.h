
#ifndef STRING_STRING_JOINER_H
#define STRING_STRING_JOINER_H

#include "../../../Joiner.h"

class StringStringJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
