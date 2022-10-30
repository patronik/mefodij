
#ifndef ARRAY_DOUBLE_JOINER_H
#define ARRAY_DOUBLE_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class ArrayDoubleJoiner: public Joiner 
{
 
 public:
 ArrayDoubleJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
