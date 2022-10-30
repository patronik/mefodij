
#ifndef INT_ARRAY_JOINER_H
#define INT_ARRAY_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class IntArrayJoiner : public Joiner 
{
 
 public:
 IntArrayJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
