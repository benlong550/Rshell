#ifndef __OR_H__
#define __OR_H__

#include "Connector.h"

class Or: public Connector {
    //constructors
    public:
    Or(Base* lhs, Base* rhs);
    Or();
    //execute function
    virtual bool execute(int in, int out);
};

//Constructors
Or::Or(Base* lhs, Base* rhs): Connector(lhs,rhs) {}
Or::Or(): Connector() {}

//executes its right child if its left child has executed
//returns true if both children execute successfully
//otherwise returns false
bool Or::execute(int in, int out) {
    if(!lhs->execute(in,out)) {
        if(rhs->execute(in,out)) {
            return true;
        }
        else {
            return false;
        }
    }
    return true;
}


#endif