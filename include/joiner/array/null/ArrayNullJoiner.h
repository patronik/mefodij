
#ifndef ARRAY_NULL_JOINER_H
#define ARRAY_NULL_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class ArrayNullJoiner: public Joiner 
{
 
 public:
 ArrayNullJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
