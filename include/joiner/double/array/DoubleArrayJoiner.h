
#ifndef DOUBLE_ARRAY_JOINER_H
#define DOUBLE_ARRAY_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class DoubleArrayJoiner: public Joiner 
{
 
 public:
 DoubleArrayJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
