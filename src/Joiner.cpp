#include "../include/Joiner.h"

void Joiner::validate(wstring op) 
{
    if (find(operators.begin(), operators.end(), op) == operators.end()) {
       throw runtime_error("Operator " + string(op.begin(), op.end()) + " is not supported");
    } 
}