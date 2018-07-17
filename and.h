#ifndef __AND_H__
#define __AND_H__

#include "connector.h"

class And: public Connector {
    public:
    //constructors
    And(Base* lhs, Base* rhs);
    And();
    virtual bool execute(int in, int out);
};

And::And(Base* lhs, Base* rhs): connector(lhs,rhs) {}

And::And(): Connector() {}

//executes its right child if its left child has executed
//returns true if both children execute successfully
//otherwise returns false
bool And::execute(int in, int out) {
    if(lhs->execute(in,out)){
       if(rhs->execute(in,out)){
           return true;
       }
       else {
           return false;
       }
    }
    else {
        return false;
     }
}
#endif