
#ifndef NULL_ARRAY_JOINER_H
#define NULL_ARRAY_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class NullArrayJoiner: public Joiner 
{
 
 public:
 NullArrayJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
