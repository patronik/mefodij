
#ifndef NULL_INT_JOINER_H
#define NULL_INT_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class NullIntJoiner: public Joiner 
{
 
 public:
 NullIntJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
