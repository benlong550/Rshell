#ifndef __OUTPUT_REDIRECTION2_H
#define __OUTPUT_REDIRECTION2_H

#include "connector.h"


class output_redirection2: public connector {
    public:
    output_redirection2(Base* lhs, Base* rhs);
    output_redirection2();
    virtual bool execute(int in, int out);
};

output_redirection2::output_redirection2(Base* lhs, Base* rhs): connector(lhs,rhs) {}

output_redirection2::output_redirection2(): connector() {}

//appends the output of a command onto a given line
//if the file does not exist in creates it
bool output_redirection2::execute(int in, int out) 
{
    string outfile = rhs->get_data();
    out = open(outfile.c_str(), O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

    return lhs->execute(0,out);
}

#endif