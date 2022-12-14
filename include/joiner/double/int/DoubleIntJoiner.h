
#ifndef DOUBLE_INT_JOINER_H
#define DOUBLE_INT_JOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class DoubleIntJoiner: public Joiner 
{
 
 public:
 DoubleIntJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
