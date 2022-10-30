
#ifndef STRING_NULL_JOINER_H
#define STRING_NULL_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class StringNullJoiner: public Joiner 
{
 
 public:
 StringNullJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
