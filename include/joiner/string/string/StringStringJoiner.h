
#ifndef STRING_STRING_JOINER_H
#define STRING_STRING_JOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class StringStringJoiner: public Joiner 
{
 
 public:
 StringStringJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
