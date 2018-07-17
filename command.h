#ifndef __CMD_H__
#define __CMD_H__

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <queue>

#include "Base.h"

using namespace std;

class Command: public Base {
    protected:
    char *command; //name of the command
    queue<char*> flags; //vector holding the flags provided
    public:
    //constructors
    Command(char *command, queue<char*> flags);
    Command(queue<char*> flags);
    Command(char *command);
    Command();

    //Adds a flag based on the container that is used (I.E. queue)
    void add_flag(char *a);
    //executes the command using the system calls fork
    //execvp and wait returns true if the command is executed
    //and false if it fails
    virtual bool execute(int in, int out);


    //For Debugging Purposes
    string get_data();

    //void printFlags();
};


//constructors
Command::Command(char* command, queue<char *> flags) {
    this->command = command;
    this->flags = flags;
}

Command::Command(queue<char*> flags) {
    this->flags = flags;
}

Command::Command(char* command) {
    this->command = command;
    queue<char*> temp;
    this->flags = temp;
}

Command::Command() {}

//push any new flags into the queue<char *> flags
void Command::add_flag(char*a) {
    flags.push(a);
}

//Used for the Exit Command to fix Exit bug
string Command::get_data() {
    return command;
}

/*For Debugging Purposes
void Command::printFlags()   {
    for(unsigned i=0; i<flags.size(); i++)  {
        cout << flags.at(i) << " ";
    }
}*/

//executes the command using the system calls fork
//execvp and wait returns true if the command is executed
//and false if it fails
bool Command::execute(int in, int out) {
    //c-string array to pass to execvp
    //flags.push_back(NULL);

    flags.push(NULL);
    int ctr = 1;
    char *args[500];
    while(flags.size() != 0) {
        args[ctr] = flags.front();
        flags.pop();
        ctr++;
    }

    args[0] = command; //Setting the Command to args[0] for execvp
    //return value of the function
    //true if command executes
    bool ret = true;

    pid_t pid = fork();                         //Creating child process
    if(pid == -1) {                             //if fork() fails
        perror("fork");                         //run error checking
    }
    else if (pid == 0) {
        // changes the input and outputs as specified on the command line
        if(dup2(in,0) == -1) {
            perror("dup2");
            return false;
        }
        if(dup2(out,1) == -1) {
            perror("dup2");
            return false;
        }

        if(execvp(args[0], args) == -1) {       //if child fail, perform error checking and return false and exit
            ret = false;
            perror("execvp");
            exit(1);
        }
    }
    else if(pid > 0) {                          //Otherwise continue to the parent process
       int status;
       if(waitpid(pid,&status,0) == -1) {       //pause the parent process
           perror("wait");
       }
       if(WEXITSTATUS(status) != 0) {
           ret = false;
       }

    }
    return ret;
}
#endif