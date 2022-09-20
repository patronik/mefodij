
#ifndef BOOL_STRING_JOINER_H
#define BOOL_STRING_JOINER_H

#include "../../../Joiner.h"

class BoolStringJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
