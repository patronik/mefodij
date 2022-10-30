
#ifndef STRING_BOOL_JOINER_H
#define STRING_BOOL_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class StringBoolJoiner: public Joiner 
{
 
 public:
 StringBoolJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
