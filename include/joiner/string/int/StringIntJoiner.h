
#ifndef STRING_INT_JOINER_H
#define STRING_INT_JOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class StringIntJoiner: public Joiner 
{
 
 public:
 StringIntJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
