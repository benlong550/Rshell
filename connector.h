#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "Base.h"
#include <cstdlib>
using namespace std;

class Connector: public Base {
    protected:

    Base* lhs; //left hand operand of the connector
    Base* rhs; //right hand operand of the connector

    public:

    //constructors
    Connector(Base* lhs, Base* rhs);
    Connector();

    virtual bool execute(int in, int out) = 0; //execute function to be overridden by derived classes
    virtual string get_data();
};

Connector::Connector(Base* lhs, Base* rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

Connector::Connector()  {
    this->lhs = NULL;
    this->lhs = NULL;
}
string Connector::get_data() {
    return "error called get data on connector";
}

#endif