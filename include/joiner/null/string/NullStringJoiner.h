
#ifndef NULL_STRING_JOINER_H
#define NULL_STRING_JOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class NullStringJoiner: public Joiner 
{
 
 public:
 NullStringJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
