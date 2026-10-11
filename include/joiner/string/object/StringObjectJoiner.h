#ifndef STRINGOBJECTJOINER_H
#define STRINGOBJECTJOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class StringObjectJoiner: public Joiner 
{
 
 public:
 StringObjectJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
