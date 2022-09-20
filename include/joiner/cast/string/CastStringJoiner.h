
#ifndef CAST_STRING_JOINER_H
#define CAST_STRING_JOINER_H

#include "../../../Joiner.h"

class CastStringJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
