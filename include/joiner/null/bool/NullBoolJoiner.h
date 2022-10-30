
#ifndef NULL_BOOL_JOINER_H
#define NULL_BOOL_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class NullBoolJoiner: public Joiner 
{
 
 public:
 NullBoolJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
