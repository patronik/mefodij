
#ifndef BOOL_BOOL_JOINER_H
#define BOOL_BOOL_JOINER_H

#include "../../../Joiner.h"

class BoolBoolJoiner : public Joiner 
{
 
 public:

 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

#endif
