#ifndef __OUTPUT_REDIRECTION_H__
#define __OUTPUT_REDIRECTION_H__

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <fcntl.h>

#include "connector.h"

using namespace std;

class output_redirection: public connector {
    public:
    output_redirection(Base* lhs, Base* rhs);
    output_redirection();
    virtual bool execute(int in, int out);
};

output_redirection::output_redirection(Base* lhs, Base* rhs): connector(lhs,rhs) {}
output_redirection::output_redirection(): connector() {}

//writes the output of a command line onto a given file
//if the file does not exist it creates it
bool output_redirection::execute(int in, int out) {
    string outfile = rhs->get_data();
    out = open(outfile.c_str(),O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

    return lhs->execute(0,out);
}

#endif