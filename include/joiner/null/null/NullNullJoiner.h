
#ifndef NULL_NULL_JOINER_H
#define NULL_NULL_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class NullNullJoiner: public Joiner 
{
 
 public:
 NullNullJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
