#ifndef __SEMICOLON_H__
#define __SEMICOLON_H__

#include "connector.h"

class Semicolon: public Connector {
    public:
    //constructors
    Semicolon(Base* lhs, Base* rhs);
    Semicolon();

    //executes both of its children regardless of the success of the
    //other child
    //returns true or false based on the success of the right child
    virtual bool execute(int in, int out);
};

//constructors
Semicolon::Semicolon(Base* lhs, Base* rhs): Connector(lhs,rhs) {}
Semicolon::Semicolon(): Connector() {}

//executes both of its children regardless of the success of the
//other child
//returns true or false based on the success of the right child
bool Semicolon::execute(int in, int out) {
    lhs->execute(in,out);
    if(rhs->execute(in,out)) {
        return true;
    }
    else {
        return false;
   }
}

#endif