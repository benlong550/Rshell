#ifndef __INPUT_REDIRECTION_H__
#define __INPUT_REDIRECTION_H__

#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <fcntl.h>
#include <string>

#include "connector.h"

class input_redirection: public Connector {
  public:
  input_redirection(Base* rhs, Base* lhs);
  input_redirection();
  virtual bool execute(int in, int out);

};

using namespace std;

input_redirection::input_redirection(Base* lhs, Base* rhs): Connector(lhs,rhs) {}

input_redirection::input_redirection(): Connector() {}

//redirects input from the standard in to the input given on the command line
bool input_redirection::execute(int in, int out) {
    string infile = rhs->get_data();
    in = open(infile.c_str(),O_RDONLY);

    return lhs->execute(in,1);
}

#endif