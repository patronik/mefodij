
#ifndef BOOL_DOUBLE_JOINER_H
#define BOOL_DOUBLE_JOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class BoolDoubleJoiner: public Joiner 
{
 
 public:
 BoolDoubleJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
