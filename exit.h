#ifndef __EXIT_H__
#define __EXIT_H__

#include "command.h"

class Exit: public Command {
    public:
    Exit();
    virtual bool execute(int in, int out);
    virtual string get_data();
};

//Constructors
Exit::Exit()
{}

bool Exit::execute(int in, int out) {
    exit(0);
}

string Exit::get_data() {
    return "Exit";
}
#endif