
#ifndef BOOL_ARRAY_JOINER_H
#define BOOL_ARRAY_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class BoolArrayJoiner: public Joiner 
{
 
 public:
 BoolArrayJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
