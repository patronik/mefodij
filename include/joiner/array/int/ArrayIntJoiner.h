
#ifndef ARRAY_INT_JOINER_H
#define ARRAY_INT_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class ArrayIntJoiner: public Joiner 
{
 
 public:
 ArrayIntJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
