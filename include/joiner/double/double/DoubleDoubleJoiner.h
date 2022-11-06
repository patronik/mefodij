
#ifndef DOUBLE_DOUBLE_JOINER_H
#define DOUBLE_DOUBLE_JOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class DoubleDoubleJoiner: public Joiner 
{
 
 public:
 DoubleDoubleJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
