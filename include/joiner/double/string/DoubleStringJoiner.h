
#ifndef DOUBLE_STRING_JOINER_H
#define DOUBLE_STRING_JOINER_H

#include "../../../Joiner.h"

class DoubleStringJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
