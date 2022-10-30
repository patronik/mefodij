
#ifndef INT_DOUBLE_JOINER_H
#define INT_DOUBLE_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class IntDoubleJoiner : public Joiner 
{
 
 public:
 IntDoubleJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
