
#ifndef BOOL_NULL_JOINER_H
#define BOOL_NULL_JOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class BoolNullJoiner: public Joiner 
{
 
 public:
 BoolNullJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
