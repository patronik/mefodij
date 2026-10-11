#ifndef OBJECTSTRINGJOINER_H
#define OBJECTSTRINGJOINER_H

#include "../../../Joiner.h"

namespace Mefodij {

class ObjectStringJoiner: public Joiner 
{
 
 public:
 ObjectStringJoiner();
 void join(shared_ptr<Atom> left, wstring op, shared_ptr<Atom> right);

};

}

#endif
