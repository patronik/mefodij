
#ifndef BOOL_INT_JOINER_H
#define BOOL_INT_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class BoolIntJoiner: public Joiner 
{
 
 public:
 BoolIntJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
