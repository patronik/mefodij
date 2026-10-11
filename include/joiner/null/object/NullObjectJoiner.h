#ifndef NULLOBJECTJOINER_H
#define NULLOBJECTJOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class NullObjectJoiner: public Joiner 
{
 
 public:
 NullObjectJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
