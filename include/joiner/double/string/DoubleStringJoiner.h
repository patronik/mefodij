
#ifndef DOUBLE_STRING_JOINER_H
#define DOUBLE_STRING_JOINER_H

#include "../../../Joiner.h"

namespace Mefody {

class DoubleStringJoiner: public Joiner 
{
 
 public:
 DoubleStringJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
