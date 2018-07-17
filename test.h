#ifndef __TEST_H__
#define __TEST_H__

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <sstream>
#include <dirent.h>
#include <iostream>

#include "Base.h"

using namespace std;

class Test: public Base {
    protected:
    char *command; //name of the command
    queue<char*> flags; //vector holding the flags provided

	public:
    Test(char *command, queue<char*> flags);
    Test(queue<char*> flags);
    Test();

    //Adds a flag based on the container that is used (I.E. queue)
    void add_flag(char *a);
    //executes the command using the system calls fork
    //execvp and wait returns true if the command is executed
    //and false if it fails
    virtual bool execute(int in, int out);

    //For Debugging Purposes
    string get_data();
};

Test::Test(char* command, queue<char *> flags) {
    this->command = command;
    this->flags = flags;
}

Test::Test(queue<char*> flags) {
    this->flags = flags;
}

Test::Test() {}

//push any new flags into the queue<char *> flags
void Test::add_flag(char*a) {
    flags.push(a);
}

//Used for the Exit Command to fix Exit bug
string Test::get_data() {
    return command;
}

//executes the test according the flag specified
//if flag == -e it will be tested to see if it is either a directory or a regular file
//if flag == -f it will be tested to see if it is a regular file
//if flag == -d it will be tested to see if it is a directory
//if no flag is provided then -e will be assumed
bool Test::execute(int in, int out) {
    struct stat buf;
    string flag;
    string path;
    bool exists = false;

    if(flags.size() == 1) {
        flag = "-e";
        path = flags.front();
    }
    else {
        //cout << flags.front() << endl;
        flag = flags.front();
        flags.pop();
        //cout << flags.front() << endl;
        path = flags.front();
    }

    //cout << path << endl;
    int statret = stat(path.c_str(),&buf);
    if (statret == 0) {
        exists = true;
    }

    if(dup2(out,1) == -1) {
        perror("dup2");
        return false;
    }

    if(statret == -1) {
        perror("stat");
        return false;
    }

    if(flag == "-e") {
        cout << "(true)" << endl;
        return exists;
    }
    else if(flag == "-d") {
        if(S_ISDIR(buf.st_mode)) {
            cout << "(true)" << endl;
            return true;
        }
        else {
            cout << "(false)" << endl;
            return false;
        }
    }
    else if(flag == "-f") {
         if(S_ISREG(buf.st_mode)) {
             cout << "(true)" << endl;
             return true;
         }
        else {
            cout << "(false)" << endl;
            return false;
        }
    }
    else {
        cout << "Error: In test flag " << flag << " is not valid."  << endl;
        return false;
    }
}
#endif